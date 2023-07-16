#include <arch/abi.h>
#include <lunaix/exec.h>
#include <lunaix/fs.h>
#include <lunaix/load.h>
#include <lunaix/mm/mmap.h>
#include <lunaix/mm/valloc.h>
#include <lunaix/mm/vmm.h>
#include <lunaix/process.h>
#include <lunaix/spike.h>
#include <lunaix/status.h>
#include <lunaix/syscall.h>
#include <lunaix/syscall_utils.h>

#include <klibc/string.h>

void
exec_container(struct exec_container* param,
               struct proc_info* proc,
               ptr_t vms,
               const char** argv,
               const char** envp)
{
    *param = (struct exec_container){ .proc = proc,
                                      .vms_mnt = vms,
                                      .exe = { .container = param },
                                      .argv_pp = { 0, 0 },
                                      .argv = argv,
                                      .envp = envp };
}

size_t
exec_str_size(const char** str_arr, size_t* length)
{
    if (!str_arr) {
        *length = 0;
        return 0;
    }

    const char* chr = *str_arr;
    size_t sz = 0, len = 0;

    while (chr) {
        sz += strlen(chr);
        len++;

        chr = *(str_arr++);
    }

    *length = len;
    return sz + sizeof(char*);
}

// externed from mm/dmm.c
extern int
create_heap(struct proc_mm* pvms, ptr_t addr);

int
exec_load(struct exec_container* container, struct v_file* executable)
{
    int errno = 0;

    const char **argv = container->argv, **envp = container->envp;
    size_t argv_len, envp_len;
    size_t sz_argv = exec_str_size(argv, &argv_len);
    size_t sz_envp = exec_str_size(envp, &envp_len);
    size_t var_sz = ROUNDUP(sz_envp, PG_SIZE);
    const char** argv_extra = container->argv_pp;

    argv_extra[0] = executable->dnode->name.value;

    if (var_sz / PG_SIZE > MAX_VAR_PAGES) {
        errno = E2BIG;
        goto done;
    }

    if ((errno = load_executable(&container->exe, executable))) {
        goto done;
    }

    struct proc_mm* pvms = &container->proc->mm;

    // A dedicated place for process variables (e.g. envp)
    struct mmap_param map_vars = { .pvms = pvms,
                                   .vms_mnt = container->vms_mnt,
                                   .flags = MAP_ANON | MAP_PRIVATE | MAP_FIXED,
                                   .type = REGION_TYPE_VARS,
                                   .proct = PROT_READ,
                                   .mlen = MAX_VAR_PAGES * PG_SIZE };

    void* mapped;

    if (pvms->heap) {
        mem_unmap_region(container->vms_mnt, pvms->heap);
        pvms->heap = NULL;
    }

    if (!argv_extra[1]) {
        // If loading a statically linked file, then heap remapping we can do,
        // otherwise delayed.
        create_heap(&container->proc->mm, PG_ALIGN(container->exe.end));
    }

    if ((errno = mem_map(&mapped, NULL, UMMAP_END, NULL, &map_vars))) {
        goto done;
    }

    if (container->vms_mnt == VMS_SELF) {
        // we are loading executable into current addr space

        // make some handy infos available to user space
        if (envp)
            memcpy(mapped, (void*)envp, sz_envp);

        void* ustack = (void*)USTACK_TOP;

        if (argv) {
            ustack = (void*)((ptr_t)ustack - sz_argv);
            memcpy(ustack, (void*)argv, sz_argv);
        }

        for (size_t i = 0; i < 2 && argv_extra[i]; i++, argv_len++) {
            const char* extra_arg = argv_extra[i];
            size_t str_len = strlen(extra_arg);

            ustack = (void*)((ptr_t)ustack - str_len);
            memcpy(ustack, (const void*)extra_arg, str_len);
        }

        // four args (arg{c|v}, env{c|p}) for main
        struct uexec_param* exec_param = &((struct uexec_param*)ustack)[-1];

        container->stack_top = (ptr_t)exec_param;

        *exec_param = (struct uexec_param){
            .argc = argv_len, .argv = ustack, .envc = envp_len, .envp = mapped
        };

    } else {
        /*
            TODO need to find a way to inject argv and envp remotely
                 this is for the support of kernel level implementation of
                 posix_spawn

            IDEA
                1. Allocate a orphaned physical page (i.e., do not belong to any
                VMA)
                2. Mounted to a temporary mount point in current VMA, (i.e.,
                PG_MOUNT_*)
                3. Do setup there.
                4. Unmount then mounted to the foreign VMA as the first stack
                page.
        */
        fail("not implemented");
    }

done:
    return errno;
}

int
exec_load_byname(struct exec_container* container, const char* filename)
{
    int errno = 0;
    struct v_dnode* dnode;
    struct v_file* file;

    if ((errno = vfs_walk_proc(filename, &dnode, NULL, 0))) {
        goto done;
    }

    if ((errno = vfs_open(dnode, &file))) {
        goto done;
    }

    errno = exec_load(container, file);

done:
    return errno;
}

int
exec_kexecve(const char* filename, const char* argv[], const char* envp[])
{
    int errno = 0;
    struct exec_container container;

    exec_container(
      &container, (struct proc_info*)__current, VMS_SELF, argv, envp);

    errno = exec_load_byname(&container, filename);

    if (errno) {
        return errno;
    }

    ptr_t entry = container.exe.entry;

    assert(entry);
    j_usr(container.stack_top, entry);

    // should not reach

    return errno;
}

__DEFINE_LXSYSCALL3(int,
                    execve,
                    const char*,
                    filename,
                    const char*,
                    argv[],
                    const char*,
                    envp[])
{
    int errno = 0;
    struct exec_container container;

    exec_container(
      &container, (struct proc_info*)__current, VMS_SELF, argv, envp);

    if ((errno = exec_load_byname(&container, filename))) {
        goto done;
    }

    // we will jump to new entry point (_u_start) upon syscall's
    // return so execve 'will not return' from the perspective of it's invoker
    volatile struct exec_param* execp = __current->intr_ctx.execp;
    execp->esp = container.stack_top;
    execp->eip = container.exe.entry;

done:
    // set return value
    store_retval(DO_STATUS(errno));

    // Always yield the process that want execve!
    schedule();

    // this will never get executed!
    return -1;
}