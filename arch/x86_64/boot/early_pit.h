// SPDX-License-Identifier: GPL-3.0

/*
 * early_pit.c 
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Programmable_Interval_Timer
 */

#ifndef EARLY_PIT_H
#define EARLY_PIT_H

#include <stdint.h>

uint64_t early_calculate_tsc_freq(uint16_t pit_poll_val);

#endif // EARLY_PIT_H