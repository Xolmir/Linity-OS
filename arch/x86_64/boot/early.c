// SPDX-License-Identifier: GPL-3.0

/*
 * early.c 
 *   Early initialization for x86_64 architecture
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <boot/early_serial.h>
#include <printk.h>
#include <panic.h>
#include <kstatus.h>
#include <cpuid.h>
#include <boot/early_limine.h>
#include <boot/early_idt.h>
#include <boot/early_pic.h>
#include <boot/early_pit.h>
#include <hal/hal_cpu.h>

extern void kernel_main(void);

void early_main(void);

void early_main(void) {
    hal_cpu_irq_disable();

    kernel_state = KSTATUS_EARLY;

    validate_boot_protocol();
    
    if(early_init_serial()) {
        printk("Early serial initialization failed.");
    }
    printk("Reset\n");
    printk("KSTATUS = %d\n", kernel_state);
    
    cpuid_t cpu_info;
    cpuid(0x80000007, 0, &cpu_info);
    if ((cpu_info.edx & (1 << 8)) == 0) {
        kernel_state = KSTATUS_EARLY_PANIC;
        panic("Invariant TSC not found.");
    }

    early_idt_init();
    early_pic_disable();
    uint64_t cpu_freq = early_calculate_tsc_freq(0xFFFF);
    uint64_t cpu_freq_ghz = (cpu_freq / 1000000000);
    uint64_t cpu_freq_mhz = (cpu_freq % 1000000000) / 1000000;
    printk("CPU Ghz : %lu.%lu Ghz\n", cpu_freq_ghz, cpu_freq_mhz);
    printk("CPU Hz : %lu Hz\n", cpu_freq);

    kernel_main();
}
