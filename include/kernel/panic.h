// SPDX-License-Identifier: GPL-3.0

/*
 * panic.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#ifndef PANIC_H
#define PANIC_H

__attribute__((noreturn))
void panic(const char* fmt, ...);

#endif // PANIC_H
