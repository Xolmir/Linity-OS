// SPDX-License-Identifier: GPL-3.0

/*
 * hal_cpu_impl.c 
 *   Architecture-specific CPU management functions
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <hal/hal_cpu.h>
#include <kstatus.h>

void hal_cpu_irq_disable(void) {
    switch (kernel_state) {
        case KSTATUS_EARLY: {
            __asm__ volatile ("cli");
            break;
        }
        case KSTATUS_EARLY_PANIC: {
            __asm__ volatile ("cli");
            break;
        }
        case KSTATUS_RUNNING:
        case KSTATUS_PANIC: {
            break;
        }
        default: {
            __asm__ volatile ("cli");
            break;
        }
    }
}

void hal_cpu_irq_enable(void) {
    switch (kernel_state) {
        case KSTATUS_EARLY: {
            __asm__ volatile ("sti");
            break;
        }
        case KSTATUS_EARLY_PANIC: {
            __asm__ volatile ("sti");
            break;
        }
        case KSTATUS_RUNNING:
        case KSTATUS_PANIC: {
            break;
        }
        default: {
            __asm__ volatile ("sti");
            break;
        }
    }
}

void hal_cpu_halt(void) {
    switch (kernel_state) {
        case KSTATUS_EARLY: {
            for (;;)
                __asm__ volatile ("hlt");
            break;
        }
        case KSTATUS_EARLY_PANIC: {
            for (;;)
                __asm__ volatile ("hlt");
            break;
        }
        case KSTATUS_RUNNING:
        case KSTATUS_PANIC: {
            break;
        }
        default: {
            for (;;)
                __asm__ volatile ("hlt");
            break;
        }
    }
}