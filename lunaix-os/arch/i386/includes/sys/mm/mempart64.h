#ifndef __LUNAIX_MEMPART64_H
#define __LUNAIX_MEMPART64_H

#define END_POINT(name) (name + name##_SIZE - 1)

#define KSTACK_AREA             0x0000000040000000UL
#define KSTACK_AREA_SIZE        0x0000000040000000UL
#define KSTACK_AREA_END END_POINT(KSTACK_AREA)

#define USR_EXEC                0x0000008000000000UL
#define USR_EXEC_SIZE           0x0000002000000000UL
#define USR_EXEC_END END_POINT(USR_EXEC)

#define USR_MMAP                0x0000010000000000UL
#define USR_MMAP_SIZE           0x0000008000000000UL
#define USR_MMAP_END END_POINT(USR_MMAP)

#define USR_STACK               0x0000018000000000UL
#define USR_STACK_SIZE          0x0000000200000000UL
#define USR_STACK_END END_POINT(USR_STACK)

#define KERNEL_IMG              0xfffffe0000000000UL
#define KERNEL_IMG_SIZE         0x0000000400000000UL
#define KERNEL_IMG_END END_POINT(KERNEL_IMG)

#define VMAP                    0xfffffe0400000000UL
#define VMAP_SIZE               0x0000007c00000000UL
#define VMAP_END END_POINT(VMAP)

#define PG_MOUNT_1              0xfffffe8000000000UL
#define PG_MOUNT_1_SIZE         0x0000000000001000UL
#define PG_MOUNT_1_END END_POINT(PG_MOUNT_1)

#define PG_MOUNT_2              0xfffffe8000001000UL
#define PG_MOUNT_2_SIZE         0x0000000000001000UL
#define PG_MOUNT_2_END END_POINT(PG_MOUNT_2)

#define PG_MOUNT_3              0xfffffe8000002000UL
#define PG_MOUNT_3_SIZE         0x0000000000001000UL
#define PG_MOUNT_3_END END_POINT(PG_MOUNT_3)

#define PG_MOUNT_4              0xfffffe8000003000UL
#define PG_MOUNT_4_SIZE         0x0000000000001000UL
#define PG_MOUNT_4_END END_POINT(PG_MOUNT_4)

#define PG_MOUNT_VAR            0xfffffe8000004000UL
#define PG_MOUNT_VAR_SIZE       0x0000007fffffc000UL
#define PG_MOUNT_VAR_END END_POINT(PG_MOUNT_VAR)

#define VMS_MOUNT_1             0xffffff0000000000UL
#define VMS_MOUNT_1_SIZE        0x0000008000000000UL
#define VMS_MOUNT_1_END END_POINT(VMS_MOUNT_1)

#endif