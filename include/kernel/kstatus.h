// SPDX-License-Identifier: GPL-3.0

/*
 * kstatus.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#ifndef KSTATUS_H
#define KSTATUS_H

typedef enum {
    KSTATUS_NOT_SET = 0,
    KSTATUS_EARLY,
    KSTATUS_EARLY_PANIC,
    KSTATUS_RUNNING,
    KSTATUS_PANIC
} kernel_status_t;

extern kernel_status_t kernel_state;

#endif // KSTATUS_H