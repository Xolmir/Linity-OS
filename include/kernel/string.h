// SPDX-License-Identifier: GPL-3.0

/*
 * string.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void* memset(void* dest, int value, size_t count);
void* memcpy(void* restrict dest, const void* restrict src, size_t count);
void* memmove(void* dest, const void* src, size_t count);
int memcmp(const void* lhs, const void* rhs, size_t count);

#endif // STRING_H