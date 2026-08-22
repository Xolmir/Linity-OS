// SPDX-License-Identifier: GPL-3.0

/*
 * memmove.c
 *   Memory move function
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <stdint.h>
#include <string.h>

void* memmove(void* dest, const void* src, size_t count) {
    unsigned char* dst = dest;
    const unsigned char* source = src;

    if (dst == source)
        return dest;

    if ((uintptr_t)dst < (uintptr_t)source)
        for (size_t i = 0; i < count; i++)
            dst[i] = source[i];
    else
        for (size_t i = count; i > 0; i--)
            dst[i - 1] = source[i - 1];

    return dest;
}