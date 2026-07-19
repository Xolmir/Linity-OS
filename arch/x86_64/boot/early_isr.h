// SPDX-License-Identifier: GPL-3.0

/*
 * early_isr.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Interrupt_Service_Routines
 */

#ifndef EARLY_ISR_H
#define EARLY_ISR_H

#include <stdint.h>

__attribute__((interrupt)) void early_divide_zero_exp(void* frame);
__attribute__((interrupt)) void early_debug_exp(void* frame);
__attribute__((interrupt)) void early_non_maskable_int_exp(void* frame);
__attribute__((interrupt)) void early_breakpoint_exp(void* frame);
__attribute__((interrupt)) void early_overflow_exp(void* frame);
__attribute__((interrupt)) void early_bound_range_exceeded_exp(void* frame);
__attribute__((interrupt)) void early_invalid_opcode_exp(void* frame);
__attribute__((interrupt)) void early_device_not_available_exp(void* frame);
__attribute__((interrupt)) void early_coprocessor_seg_overrun_exp(void* frame);
__attribute__((interrupt)) void early_intel_reserved_exp(void* frame);
__attribute__((interrupt)) void early_x87_fpu_exp(void* frame);
__attribute__((interrupt)) void early_machine_exp(void* frame);
__attribute__((interrupt)) void early_SIMD_exp(void* frame);
__attribute__((interrupt)) void early_virtual_exp(void* frame);
__attribute__((interrupt)) void early_reserved_exp(void* frame);

__attribute__((interrupt)) void early_double_fault_exp(void* frame, unsigned long int error_code);
__attribute__((interrupt)) void early_invalid_tss_exp(void* frame, unsigned long int error_code);
__attribute__((interrupt)) void early_segment_not_present_exp(void* frame, unsigned long int error_code);
__attribute__((interrupt)) void early_stack_seg_exp(void* frame, unsigned long int error_code);
__attribute__((interrupt)) void early_general_protect_exp(void* frame, unsigned long int error_code);
__attribute__((interrupt)) void early_page_fault_exp(void* frame, unsigned long int error_code);
__attribute__((interrupt)) void early_alignment_exp(void* frame, unsigned long int error_code);
__attribute__((interrupt)) void early_control_protect_exp(void* frame, unsigned long int error_code);

void early_get_all_exp_func(uintptr_t* isr_vector_table);

#endif // EARLY_ISR_H