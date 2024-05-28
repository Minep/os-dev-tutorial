#include <lunaix/mm/valloc.h>

#include "ext2.h"

void
ext2gd_prepare_gdt(struct v_superblock* vsb)
{
    struct ext2b_super* sb;
    unsigned int nr_parts;
    unsigned int nr_gd_pb, nr_gd;
    struct ext2_sbinfo* ext2sb;

    ext2sb = EXT2_SB(vsb);
    sb = &ext2sb->raw;
    
    nr_gd_pb = ext2sb->block_size / sizeof(struct ext2b_gdesc);
    nr_gd    = ICEIL(sb->s_blk_cnt, sb->s_blk_per_grp);
    nr_parts = ICEIL(nr_gd, nr_gd_pb);

    ext2sb->gdt_frag    = (bbuf_t*)vcalloc(sizeof(bbuf_t), nr_parts);
    ext2sb->nr_gdesc_pb = nr_gd_pb;
    ext2sb->nr_gdesc    = nr_gd;
}

void
ext2gd_release_gdt(struct v_superblock* vsb)
{
    unsigned int parts_cnt;
    struct ext2_sbinfo* ext2sb;

    ext2sb = EXT2_SB(vsb);
    parts_cnt = ICEIL(ext2sb->nr_gdesc, ext2sb->nr_gdesc_pb);
    for (size_t i = 0; i < parts_cnt; i++)
    {
        if (!ext2sb->gdt_frag[i]) {
            continue;
        }

        fsblock_put(ext2sb->gdt_frag[i]);
        ext2sb->gdt_frag[i] = NULL;
    }
}

int
ext2gd_desc_at(struct v_superblock* vsb, 
               unsigned int index, struct ext2b_gdesc** out)
{
    bbuf_t part;
    struct ext2_sbinfo* ext2sb;
    unsigned int blk_id, blk_off;

    ext2sb = EXT2_SB(vsb);

    if (index >= ext2sb->nr_gdesc) {
        return ENOENT;
    }

    blk_id  = index / ext2sb->nr_gdesc_pb;
    blk_off = index % ext2sb->nr_gdesc_pb;
    
    part = ext2sb->gdt_frag[blk_id];
    if (!part) {
        blk_id = ext2_datablock(ext2sb, blk_id) + 1;
        part   = fsblock_take(vsb, blk_id);
        if (blkbuf_errbuf(part)) {
            return EIO;
        }
        
        ext2sb->gdt_frag[blk_id] = part;
    }

    *out = &block_buffer(part, struct ext2b_gdesc)[blk_off];

    return 0;
}