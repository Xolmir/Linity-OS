// SPDX-License-Identifier: GPL-3.0

/*
 * early_serial.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Serial_Ports
 */

#ifndef EARLY_SERIAL_H
#define EARLY_SERIAL_H

#include <stdint.h>
 
int early_init_serial(void);
void early_serial_write_char(char character);

#endif // EARLY_SERIAL_H