// SPDX-License-Identifier: GPL-3.0

/*
 * early_isr.c 
 *   Early Interrupt Service Routine (ISR) definitions
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Interrupt_Service_Routines
 */

#include <stdint.h>
#include <panic.h>
#include <boot/early_isr.h>
#include <boot/early_pic.h>

__attribute__((interrupt)) void early_divide_zero_exp(void* frame) {
    panic("Divide by zero exception");
}
__attribute__((interrupt)) void early_debug_exp(void* frame) {
    panic("Debug exception");
}
__attribute__((interrupt)) void early_non_maskable_int_exp(void* frame) {
    panic("Non-maskable interrupt exception");
}
__attribute__((interrupt)) void early_breakpoint_exp(void* frame) {
    panic("Breakpoint exception");
}
__attribute__((interrupt)) void early_overflow_exp(void* frame) {
    panic("Overflow exception");
}
__attribute__((interrupt)) void early_bound_range_exceeded_exp(void* frame) {
    panic("Bound range exceeded exception");
}
__attribute__((interrupt)) void early_invalid_opcode_exp(void* frame) {
    panic("Invalid opcode exception");
}
__attribute__((interrupt)) void early_device_not_available_exp(void* frame) {
    panic("Device not available exception");
}
__attribute__((interrupt)) void early_coprocessor_seg_overrun_exp(void* frame) {
    panic("Coprocessor segment overrun exception");
}
__attribute__((interrupt)) void early_intel_reserved_exp(void* frame) {
    panic("Intel reserved exception");
}
__attribute__((interrupt)) void early_x87_fpu_exp(void* frame) {
    panic("x87 FPU floating-point exception");
}
__attribute__((interrupt)) void early_machine_exp(void* frame) {
    panic("Machine check exception");
}
__attribute__((interrupt)) void early_SIMD_exp(void* frame) {
    panic("SIMD floating-point exception");
}
__attribute__((interrupt)) void early_virtual_exp(void* frame) {
    panic("Virtualization exception");
}
__attribute__((interrupt)) void early_reserved_exp(void* frame) {
    panic("Reserved exception");
}

__attribute__((interrupt)) void early_double_fault_exp(void* frame, unsigned long int error_code) {
    panic("Double fault exception, error code: %llu", error_code);
}
__attribute__((interrupt)) void early_invalid_tss_exp(void* frame, unsigned long int error_code) {
    panic("Invalid TSS exception, error code: %llu", error_code);
}
__attribute__((interrupt)) void early_segment_not_present_exp(void* frame, unsigned long int error_code) {
    panic("Segment not present exception, error code: %llu", error_code);
}
__attribute__((interrupt)) void early_stack_seg_exp(void* frame, unsigned long int error_code) {
    panic("Stack segment fault exception, error code: %llu", error_code);
}
__attribute__((interrupt)) void early_general_protect_exp(void* frame, unsigned long int error_code) {
    panic("General protection fault exception, error code: %llu", error_code);
}
__attribute__((interrupt)) void early_page_fault_exp(void* frame, unsigned long int error_code) {
    panic("Page fault exception, error code: %llu", error_code);
}
__attribute__((interrupt)) void early_alignment_exp(void* frame, unsigned long int error_code) {
    panic("Alignment check exception, error code: %llu", error_code);
}
__attribute__((interrupt)) void early_control_protect_exp(void* frame, unsigned long int error_code) {
    panic("Control protection exception, error code: %llu", error_code);
}

void early_get_all_exp_func(uintptr_t* isr_vector_table) {
    isr_vector_table[0]  = (uintptr_t)early_divide_zero_exp;
    isr_vector_table[1]  = (uintptr_t)early_debug_exp;
    isr_vector_table[2]  = (uintptr_t)early_non_maskable_int_exp;
    isr_vector_table[3]  = (uintptr_t)early_breakpoint_exp;
    isr_vector_table[4]  = (uintptr_t)early_overflow_exp;
    isr_vector_table[5]  = (uintptr_t)early_bound_range_exceeded_exp;
    isr_vector_table[6]  = (uintptr_t)early_invalid_opcode_exp;
    isr_vector_table[7]  = (uintptr_t)early_device_not_available_exp;
    isr_vector_table[8]  = (uintptr_t)early_double_fault_exp;
    isr_vector_table[9]  = (uintptr_t)early_coprocessor_seg_overrun_exp;
    isr_vector_table[10] = (uintptr_t)early_invalid_tss_exp;
    isr_vector_table[11] = (uintptr_t)early_segment_not_present_exp;
    isr_vector_table[12] = (uintptr_t)early_stack_seg_exp;
    isr_vector_table[13] = (uintptr_t)early_general_protect_exp;
    isr_vector_table[14] = (uintptr_t)early_page_fault_exp;
    isr_vector_table[15] = (uintptr_t)early_intel_reserved_exp;
    isr_vector_table[16] = (uintptr_t)early_x87_fpu_exp;
    isr_vector_table[17] = (uintptr_t)early_alignment_exp;
    isr_vector_table[18] = (uintptr_t)early_machine_exp;
    isr_vector_table[19] = (uintptr_t)early_SIMD_exp;
    isr_vector_table[20] = (uintptr_t)early_virtual_exp;
    isr_vector_table[21] = (uintptr_t)early_control_protect_exp;

    for (int i = 22; i < 32; i++) {
        isr_vector_table[i] = (uintptr_t)early_reserved_exp;
    }
}