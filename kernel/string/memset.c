// SPDX-License-Identifier: GPL-3.0

/*
 * memset.c
 *   Memory set function
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <string.h>

void* memset(void *dest, int value, size_t count) {
    unsigned char* dst = dest;
    const unsigned char val = (unsigned char)value;
    
    for (size_t i = 0; i < count; i++)
        dst[i] = val;
    return dest;
}