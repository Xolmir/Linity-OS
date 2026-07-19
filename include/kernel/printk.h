// SPDX-License-Identifier: GPL-3.0

/*
 * printk.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#ifndef PRINTK_H
#define PRINTK_H

#include <stdarg.h>

void vprintk(const char *format, va_list args);
void printk(const char *format, ...);

#endif // PRINTK_H