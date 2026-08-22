// SPDX-License-Identifier: GPL-3.0

/*
 * hal_cpu.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#ifndef HAL_CPU_H
#define HAL_CPU_H

void hal_cpu_irq_disable(void);
void hal_cpu_irq_enable(void);
void hal_cpu_halt(void);

#endif // HAL_CPU_H