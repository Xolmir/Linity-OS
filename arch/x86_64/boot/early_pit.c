// SPDX-License-Identifier: GPL-3.0

/*
 * early_pit.c 
 *   Early Programmable Interval Timer (PIT) initialization and polling
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Programmable_Interval_Timer
 */

#include <stdint.h>
#include <io.h>
#include <boot/early_pit.h>
#include <boot/early_pic.h>
#include <panic.h>

#define EARLY_PIT_PORT_CH2    0x42
#define EARLY_PIT_PORT_CMD    0x43
#define EARLY_PIT_BASE_HZ     1193182

#define EARLY_PIT_PORT_SPK    0x61
#define EARLY_PIT_SPK_OUT_BIT (1 << 5)
#define EARLY_PIT_SPK_GATE    (1 << 0)
#define EARLY_PIT_SPK_DATA    (1 << 1)

#define EARLY_PIT_SEL_CH2     (0x02 << 6)
#define EARLY_PIT_ACC_LOHI    (0x03 << 4)

uint64_t early_calculate_tsc_freq(uint16_t pit_poll_val) {
    __asm__ volatile ("cli");

    outb(EARLY_PIT_PORT_CMD, 
        EARLY_PIT_SEL_CH2 |
        EARLY_PIT_ACC_LOHI 
    );

    outb(EARLY_PIT_PORT_CH2, (uint8_t)(pit_poll_val & 0xFF));
    outb(EARLY_PIT_PORT_CH2, (uint8_t)((pit_poll_val >> 8) & 0xFF));

    uint64_t first_tsc = rdtsc();
    
    uint8_t speaker = inb(EARLY_PIT_PORT_SPK);
    
    speaker &= ~(EARLY_PIT_SPK_GATE | EARLY_PIT_SPK_DATA);
    outb(EARLY_PIT_PORT_SPK, speaker);
    speaker |= EARLY_PIT_SPK_GATE;
    outb(EARLY_PIT_PORT_SPK, speaker);

    const uint64_t max_cycles = 300000000ULL; // ~300 milyon cycle
    while (1) {
        if ((inb(EARLY_PIT_PORT_SPK) & EARLY_PIT_SPK_OUT_BIT) != 0)
            break;
        if ((rdtsc() - first_tsc) > max_cycles)
            panic("PIT calibration timeout");
    }
    
    uint64_t elapsed_tsc    = rdtsc() - first_tsc;
    uint64_t cpu_frequency  = (elapsed_tsc * EARLY_PIT_BASE_HZ) / pit_poll_val;
    return cpu_frequency;
}