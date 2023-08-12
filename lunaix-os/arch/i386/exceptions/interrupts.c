#include <sys/interrupts.h>
#include <sys/x86_isa.h>

#include <hal/apic.h>
#include <hal/cpu.h>

#include <lunaix/isrm.h>
#include <lunaix/mm/page.h>
#include <lunaix/mm/vmm.h>
#include <lunaix/process.h>
#include <lunaix/sched.h>
#include <lunaix/syslog.h>
#include <lunaix/tty/tty.h>

#include "i386_intr.h"

LOG_MODULE("INTR")

extern x86_page_table* __kernel_ptd;

void
exception_init()
{
    exception_install_handler();
    isrm_init();
    intr_routine_init();
}

void
intr_handler(isr_param* param)
{
    param->execp->saved_prev_ctx = __current->intr_ctx;
    __current->intr_ctx = param;

    volatile struct exec_param* execp = __current->intr_ctx->execp;

    if (execp->vector <= 255) {
        isr_cb subscriber = isrm_get(execp->vector);
        subscriber(param);
        goto done;
    }

    kprint_panic("INT %u: (%x) [%p: %p] Unknown",
                 execp->vector,
                 execp->err_code,
                 execp->cs,
                 execp->eip);

done:
    // for all external interrupts except the spurious interrupt
    //  this is required by Intel Manual Vol.3A, section 10.8.1 & 10.8.5
    if (execp->vector >= IV_EX && execp->vector != APIC_SPIV_IV) {
        apic_done_servicing();
    }

    return;
}