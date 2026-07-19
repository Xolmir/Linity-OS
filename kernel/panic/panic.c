// SPDX-License-Identifier: GPL-3.0

/*
 * panic.c 
 *   Kernel panic handling functions
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <stdarg.h>
#include <kstatus.h>
#include <panic.h>
#include <printk.h>

__attribute__((noreturn))
void panic(const char* fmt, ...) {
    __asm__ volatile ("cli");
    switch (kernel_state) {
        case KSTATUS_EARLY:
        case KSTATUS_EARLY_PANIC: {
            kernel_state = KSTATUS_EARLY_PANIC;
            va_list args;
            va_start(args, fmt);

            printk("\n*** KERNEL PANIC ***\n");
            vprintk(fmt, args);

            va_end(args);
            break;
        }
        case KSTATUS_RUNNING:
        case KSTATUS_PANIC:
            kernel_state = KSTATUS_PANIC;
            break;
        default:
            kernel_state = KSTATUS_PANIC;
            break;
    }

    for (;;) {
        __asm__ volatile ("cli; hlt");
    }
}