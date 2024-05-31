#ifndef __LUNAIX_FSAPI_H
#define __LUNAIX_FSAPI_H

#include <lunaix/fs.h>
#include <lunaix/fcntl_defs.h>
#include <lunaix/blkbuf.h>

struct fsapi_vsb_ops
{
    u32_t (*read_capacity)(struct v_superblock* vsb);
    u32_t (*read_usage)(struct v_superblock* vsb);
    void (*init_inode)(struct v_superblock* vsb, struct v_inode* inode);
    void (*release)(struct v_superblock* vsb);
};

static inline struct device* 
fsapi_blockdev(struct v_superblock* vsb) 
{
    assert_fs(vsb->dev);
    return vsb->dev;
}

typedef void (*inode_init)(struct v_superblock* vsb, struct v_inode* inode) ;
typedef void (*inode_free)(struct v_inode* inode) ;

static inline void
fsapi_set_inode_initiator(struct v_superblock* vsb, inode_init inode_initiator)
{
    vsb->ops.init_inode = inode_initiator;
}

static inline void
fsapi_set_block_size(struct v_superblock* vsb, size_t block_size)
{
    vsb->blksize = block_size;
}

static inline size_t
fsapi_block_size(struct v_superblock* vsb)
{
    return vsb->blksize;
}

static inline void
fsapi_set_vsb_ops(struct v_superblock* vsb, struct fsapi_vsb_ops* basic_ops)
{
    vsb->ops.read_capacity = basic_ops->read_capacity;
    vsb->ops.read_usage = basic_ops->read_usage;
    vsb->ops.release = basic_ops->release;
    vsb->ops.init_inode = basic_ops->init_inode;
}

static inline void
fsapi_complete_vsb(struct v_superblock* vsb, void* cfs_sb)
{
    assert_fs(vsb->ops.init_inode);
    assert_fs(vsb->ops.read_capacity);
    assert_fs(vsb->blksize);

    vsb->data = cfs_sb;
    vsb->blks = blkbuf_create(block_dev(vsb->dev), vsb->blksize);
}

static inline bool
fsapi_readonly_mount(struct v_superblock* vsb)
{
    return (vsb->root->mnt->flags & MNT_RO);
}

static inline void
fsapi_set_readonly_mount(struct v_superblock* vsb)
{
    vsb->root->mnt->flags |= MNT_RO;
}

#define fsapi_impl_data(vfs_obj, type) (type*)((vfs_obj)->data)

static inline void
fsapi_inode_setid(struct v_inode* inode, 
                  inode_t i_id, unsigned int blk_addr)
{
    inode->id = i_id;
    inode->lb_addr = blk_addr;
}

static inline void
fsapi_inode_settype(struct v_inode* inode, unsigned int type)
{
    inode->itype = type;
}

static inline void
fsapi_inode_setsize(struct v_inode* inode, unsigned int fsize)
{
    inode->lb_usage = ICEIL(fsize, inode->sb->blksize);
    inode->fsize = fsize;
}

static inline void
fsapi_inode_setops(struct v_inode* inode, 
                   struct v_inode_ops* ops)
{
    inode->ops = ops;
}

static inline void
fsapi_inode_setfops(struct v_inode* inode, 
                   struct v_file_ops* fops)
{
    inode->default_fops = fops;
}

static inline void
fsapi_inode_setdector(struct v_inode* inode, 
                      inode_free free_cb)
{
    inode->destruct = free_cb;
}

static inline void
fsapi_inode_complete(struct v_inode* inode, void* data)
{
    assert_fs(inode->ops);
    assert_fs(inode->default_fops);
    assert_fs(inode->default_fops);

    inode->data = data;
}

static inline void
fsapi_inode_settime(struct v_inode* inode, 
                    time_t ctime, time_t mtime, time_t atime)
{
    inode->ctime = ctime;
    inode->mtime = mtime;
    inode->atime = atime;
}

static inline void
fsapi_dir_report(struct dir_context *dctx, 
                 const char *name, const int len, const int dtype)
{
    dctx->read_complete_callback(dctx, name, len, dtype);
}

/**
 * @brief Get a block with file-system defined block size
 *        from underlying storage medium at given block id
 *        (block address). Depending on the device attribute,
 *        it may or may not go through the block cache layer.
 * 
 * @param vsb super-block
 * @param block_id block address
 * @return bbuf_t 
 */
static inline bbuf_t
fsblock_take(struct v_superblock* vsb, unsigned int block_id)
{
    return blkbuf_take(vsb->blks, block_id);
}

/**
 * @brief put the block back into cache, recommend to pair with
 *        fsblock_take. Properly pairing will allow Lunaix to 
 *        recycle the dangling fsblock more efficient
 * 
 * @param blkbuf 
 */
static inline void
fsblock_put(bbuf_t blkbuf)
{
    return blkbuf_put(blkbuf);
}

/**
 * @brief Mark the block dirty and require scheduling a device 
 *        write request to sync it with underlying medium. Lunaix
 *        will do the scheduling when it sees fit.
 * 
 * @param blkbuf 
 */
static inline void
fsblock_dirty(bbuf_t blkbuf)
{
    return blkbuf_dirty(blkbuf);
}

/**
 * @brief Manually trigger a sync cycle, regardless the
 *        dirty property.
 * 
 * @param blkbuf 
 */
static inline void
fsblock_sync(bbuf_t blkbuf)
{
    /*
        XXX delay the sync for better write aggregation
        scheduled sync event may happened immediately (i.e., blkio queue is
        empty or nearly empty), any susequent write to the same blkbuf must
        schedule another write. Which could thrash the disk IO when intensive
        workload
    */
    return blkbuf_schedule_sync(blkbuf);
}

static inline bool
fsapi_handle_pseudo_dirent(struct v_file* file, struct dir_context* dctx) 
{
    if (file->f_pos == 0) {
        fsapi_dir_report(dctx, ".", 1, vfs_get_dtype(VFS_IFDIR));
        return true;
    }

    if (file->f_pos == 1) {
        fsapi_dir_report(dctx, "..", 2, vfs_get_dtype(VFS_IFDIR));
        return true;
    }
    
    return false;
}

#endif /* __LUNAIX_FSAPI_H */
