#include <hal/cpu.h>
#include <lunaix/clock.h>
#include <lunaix/keyboard.h>
#include <lunaix/lunistd.h>
#include <lunaix/mm/kalloc.h>
#include <lunaix/mm/vmm.h>
#include <lunaix/proc.h>
#include <lunaix/spike.h>
#include <lunaix/syslog.h>
#include <lunaix/timer.h>
#include <lunaix/tty/tty.h>

extern uint8_t __kernel_start;

LOG_MODULE("INIT")

// #define FORK_BOMB_DEMO
// #define WAIT_DEMO

void
_lxinit_main()
{
#ifdef FORK_BOMB_DEMO
    // fork炸弹
    for (;;) {
        pid_t p;
        if ((p = fork())) {
            kprintf(KDEBUG "Pinkie Pie #%d: FUN!\n", p);
        }
    }
#endif

    int status;
#ifdef WAIT_DEMO
    // 测试wait
    kprintf("I am parent, going to fork my child and wait.\n");
    if (!fork()) {
        kprintf("I am child, going to sleep for 2 seconds\n");
        sleep(2);
        kprintf("I am child, I am about to terminated\n");
        _exit(1);
    }
    pid_t child = wait(&status);
    kprintf("I am parent, my child (%d) terminated normally with code: %d.\n",
            child,
            WEXITSTATUS(status));
#endif

    pid_t p = 0;

    if (!fork()) {
        kprintf("Test no hang!");
        sleep(12);
        _exit(0);
    }

    waitpid(-1, &status, WNOHANG);

    // 这里是就是LunaixOS的第一个进程了！
    for (size_t i = 0; i < 5; i++) {
        pid_t pid = 0;
        if (!(pid = fork())) {
            sleep(i);
            if (i == 3) {
                i = *(int*)0xdeadc0de; // seg fault!
            }
            tty_put_char('0' + i);
            tty_put_char('\n');
            _exit(0);
        }
        kprintf(KINFO "Forked %d\n", pid);
    }

    while ((p = wait(&status)) >= 0) {
        short code = WEXITSTATUS(status);
        if (WIFEXITED(status)) {
            kprintf(KINFO "Process %d exited with code %d\n", p, code);
        } else {
            kprintf(KWARN "Process %d aborted with code %d\n", p, code);
        }
    }

    char buf[64];

    kprintf(KINFO "Hello processes!\n");

    cpu_get_brand(buf);
    kprintf("CPU: %s\n\n", buf);

    // no lxmalloc here! This can only be used within kernel, but here, we are
    // in a dedicated process! any access to kernel method must be done via
    // syscall

    struct kdb_keyinfo_pkt keyevent;
    while (1) {
        if (!kbd_recv_key(&keyevent)) {
            // yield();
            continue;
        }
        if ((keyevent.state & KBD_KEY_FPRESSED) &&
            (keyevent.keycode & 0xff00) <= KEYPAD) {
            tty_put_char((char)(keyevent.keycode & 0x00ff));
            tty_sync_cursor();
        }
    }

    spin();
}