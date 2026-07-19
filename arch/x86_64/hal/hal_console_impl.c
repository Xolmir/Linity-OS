// SPDX-License-Identifier: GPL-3.0

/*
 * hal_console_impl.c 
 *   Console implementation for early debugging
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <hal/hal_console.h>
#include <boot/early_serial.h>

void early_arch_debug_putc(char character) {
    early_serial_write_char(character);
}