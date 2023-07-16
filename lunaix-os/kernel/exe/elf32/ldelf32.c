#include <lunaix/exebi/elf32.h>
#include <lunaix/load.h>
#include <lunaix/mm/mmap.h>
#include <lunaix/mm/page.h>
#include <lunaix/mm/valloc.h>
#include <lunaix/spike.h>

int
elf32_smap(struct load_context* ldctx,
           const struct elf32* elf,
           struct elf32_phdr* phdre)
{
    struct v_file* elfile = (struct v_file*)elf->elf_file;

    assert(PG_ALIGNED(phdre->p_offset));

    int proct = 0;
    if ((phdre->p_flags & PF_R)) {
        proct |= PROT_READ;
    }
    if ((phdre->p_flags & PF_W)) {
        proct |= PROT_WRITE;
    }
    if ((phdre->p_flags & PF_X)) {
        proct |= PROT_EXEC;
    }

    struct exec_container* container = ldctx->container;
    struct mmap_param param = { .vms_mnt = container->vms_mnt,
                                .pvms = &container->proc->mm,
                                .proct = proct,
                                .offset = PG_ALIGN(phdre->p_offset),
                                .mlen = ROUNDUP(phdre->p_memsz, PG_SIZE),
                                .flen = phdre->p_filesz + PG_MOD(phdre->p_va),
                                .flags = MAP_FIXED | MAP_PRIVATE,
                                .type = REGION_TYPE_CODE };

    struct mm_region* seg_reg;
    int status = mem_map(NULL, &seg_reg, PG_ALIGN(phdre->p_va), elfile, &param);

    if (!status) {
        size_t next_addr = phdre->p_memsz + phdre->p_va;
        ldctx->end = MAX(ldctx->end, ROUNDUP(next_addr, PG_SIZE));
        ldctx->mem_sz += phdre->p_memsz;
    } else {
        // we probably fucked up our process
        terminate_proc(-1);
    }

    return status;
}

int
load_executable(struct load_context* context, const struct v_file* exefile)
{
    int errno = 0;

    char* ldpath = NULL;
    struct elf32 elf;
    struct exec_container* container = context->container;

    if ((errno = elf32_openat(&elf, exefile))) {
        goto done;
    }

    if (!elf32_check_exec(&elf)) {
        errno = ENOEXEC;
        goto done;
    }

    ldpath = valloc(512);
    errno = elf32_find_loader(&elf, ldpath, 512);

    if (errno < 0) {
        goto done;
    }

    if (errno != NO_LOADER) {
        container->argv_pp[1] = ldpath;

        // close old elf
        if ((errno = elf32_close(&elf))) {
            goto done;
        }

        // open the loader instead
        if ((errno = elf32_open(&elf, ldpath))) {
            goto done;
        }

        // Is this the valid loader?
        if (!elf32_static_linked(&elf) || !elf32_check_exec(&elf)) {
            errno = ELIBBAD;
            goto done_close_elf32;
        }

        // TODO: relocate loader
    } else {
        context->entry = elf.eheader.e_entry;
    }

    struct v_file* elfile = (struct v_file*)elf.elf_file;

    for (size_t i = 0; i < elf.eheader.e_phnum && !errno; i++) {
        struct elf32_phdr* phdr = &elf.pheaders[i];

        if (phdr->p_type == PT_LOAD) {
            if (phdr->p_align != PG_SIZE) {
                // surprising alignment!
                errno = ENOEXEC;
                continue;
            }

            errno = elf32_smap(context, &elf, phdr);
        }
        // TODO Handle relocation
    }

done_close_elf32:
    elf32_close(&elf);
done:
    vfree_safe(ldpath);
    return errno;
}
