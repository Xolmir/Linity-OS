// SPDX-License-Identifier: GPL-3.0

/*
 * early_pic.h 
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/8259_PIC
 */

#ifndef EARLY_PIC_H
#define EARLY_PIC_H

#include <stdint.h>

void early_pic_disable(void);

#endif // EARLY_PIC_H