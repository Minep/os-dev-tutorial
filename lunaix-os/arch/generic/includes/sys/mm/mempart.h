#ifndef __LUNAIX_ARCH_MEMPART_H
#define __LUNAIX_ARCH_MEMPART_H

#define MEM_PAGE 0x1000UL
#define MEM_1M 0x100000UL
#define MEM_4M 0x400000UL
#define MEM_HUGE 0x400000UL
#define MEM_1G 0x40000000UL

#define END_POINT(name) (name + name##_SIZE - 1)

#define KSTACK_AREA 0
#define KSTACK_AREA_SIZE 0
#define KSTACK_AREA_END END_POINT(KSTACK_AREA)

#define USR_EXEC 0
#define USR_EXEC_SIZE 0
#define USR_EXEC_END END_POINT(USR_EXEC)

#define USR_MMAP 0
#define USR_MMAP_SIZE 0
#define USR_MMAP_END END_POINT(USR_MMAP)

#define USR_STACK 0
#define USR_STACK_SIZE 0
#define USR_STACK_END END_POINT(USR_STACK)

#define KERNEL_IMG 0
#define KERNEL_IMG_SIZE 0
#define KERNEL_IMG_END END_POINT(KERNEL_IMG)

#define PG_MOUNT_1 0
#define PG_MOUNT_1_SIZE 0
#define PG_MOUNT_1_END END_POINT(PG_MOUNT_1)

#define PG_MOUNT_2 0
#define PG_MOUNT_2_SIZE 0
#define PG_MOUNT_2_END END_POINT(PG_MOUNT_2)

#define PG_MOUNT_3 0
#define PG_MOUNT_3_SIZE 0
#define PG_MOUNT_3_END END_POINT(PG_MOUNT_3)

#define PG_MOUNT_4 0
#define PG_MOUNT_4_SIZE 0
#define PG_MOUNT_4_END END_POINT(PG_MOUNT_4)

#define PG_MOUNT_VAR 0
#define PG_MOUNT_VAR_SIZE 0
#define PG_MOUNT_VAR_END END_POINT(PG_MOUNT_VAR)

#define VMAP 0
#define VMAP_SIZE 0
#define VMAP_END END_POINT(VMAP)

#define VMS_MOUNT_1 0
#define VMS_MOUNT_1_SIZE 0
#define VMS_MOUNT_1_END END_POINT(VMS_MOUNT_1)

#endif
