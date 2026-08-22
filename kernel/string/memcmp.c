// SPDX-License-Identifier: GPL-3.0

/*
 * memcmp.c
 *   Memory comparison function
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <string.h>

int memcmp(const void* lhs, const void* rhs, size_t count) {
    const unsigned char* left = lhs;
    const unsigned char* right = rhs;

    for (size_t i = 0; i < count; i++) {
        if (left[i] != right[i])
            return left[i] - right[i];
    }

    return 0;
}