// SPDX-License-Identifier: GPL-3.0

/*
 * early_pic.c 
 *   Early Programmable Interrupt Controller (PIC) disable
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/8259_PIC
 */

#include <stdint.h>
#include <io.h>
#include <boot/early_pic.h>

#define PIC_MASTER_DATA  0x21
#define PIC_SLAVE_DATA   0xA1

void early_pic_disable(void) {
    outb(PIC_MASTER_DATA, 0xFF);
    outb(PIC_SLAVE_DATA, 0xFF);
}