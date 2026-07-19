// SPDX-License-Identifier: GPL-3.0

/*
 * cpuid.h 
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/CPUID
 */

#ifndef CPUID_H
#define CPUID_H

#include <stdint.h>

typedef struct {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
} cpuid_t;

static inline void cpuid(uint32_t code, uint32_t sub, cpuid_t *res) {
    __asm__ volatile("cpuid"
                     : "=a"(res->eax), "=b"(res->ebx), "=c"(res->ecx), "=d"(res->edx)
                     : "a"(code), "c"(sub));
}

#endif // CPUID_H