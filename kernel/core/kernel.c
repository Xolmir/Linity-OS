// SPDX-License-Identifier: GPL-3.0

/*
 * kernel.c 
 *   Kernel entry point and main loop
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <kstatus.h>

kernel_status_t kernel_state;

void kernel_main(void);

void kernel_main(void) {
    kernel_state = KSTATUS_RUNNING;
    while (1) {}
}