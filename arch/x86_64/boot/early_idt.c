// SPDX-License-Identifier: GPL-3.0

/*
 * early_idt.c 
 *   Early Interrupt Descriptor Table (IDT) init and definitions
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Interrupt_Descriptor_Table
 */

#include <stdint.h>
#include <boot/early_isr.h>
#include <boot/early_pit.h>
#include <boot/early_idt.h>

#define EARLY_IDT_SIZE      32
#define EARLY_IDT_PRESENT   (1 << 7)
#define EARLY_IDT_INT_GATE  0xE

typedef struct {
    uint16_t    isr_low;
    uint16_t    kernel_cs;
    uint8_t     ist;
    uint8_t     attributes;
    uint16_t    isr_mid;
    uint32_t    isr_high;
    uint32_t    reserved;
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[EARLY_IDT_SIZE];

typedef struct {
    uint16_t    limit;
    uint64_t    base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

static void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];
    
    uint16_t current_cs;
    __asm__ volatile ("mov %%cs, %0" : "=r" (current_cs)); 

    descriptor->isr_low    = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs  = current_cs; 
    descriptor->ist        = 0;
    descriptor->attributes = flags;
    descriptor->isr_mid    = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high   = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved   = 0;
}

void early_idt_init(void) {
    idtr.base  = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * EARLY_IDT_SIZE - 1;

    uintptr_t isr_vector_table[32];
    early_get_all_exp_func(isr_vector_table);
    for (uint64_t vector = 0; vector < EARLY_IDT_SIZE; vector++) {
        idt_set_descriptor((uint8_t)vector, (void*)isr_vector_table[vector], EARLY_IDT_PRESENT | EARLY_IDT_INT_GATE); 
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr));
}