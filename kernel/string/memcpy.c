// SPDX-License-Identifier: GPL-3.0

/*
 * memcpy.c
 *   Memory copy function
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <string.h>

void* memcpy(void* restrict dest, const void* restrict src, size_t count) {
    unsigned char* dst = dest;
    const unsigned char* source = src;

    for (size_t i = 0; i < count; i++)
        dst[i] = source[i];

    return dest;
}