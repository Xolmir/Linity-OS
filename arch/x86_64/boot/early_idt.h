// SPDX-License-Identifier: GPL-3.0

/*
 * early_idt.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Interrupt_Descriptor_Table
 */

#ifndef EARLY_IDT_H
#define EARLY_IDT_H

#include <stdint.h>
#include <boot/early_isr.h>

void early_idt_init(void);

#endif // EARLY_IDT_H