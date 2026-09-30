// SPDX-License-Identifier: GPL-3.0

/*
 * early_limine.h
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Limine_Bare_Bones
 *   https://github.com/Limine-Bootloader/Limine/blob/v12.x/USAGE.md
 */

#ifndef EARLY_LIMINE_H
#define EARLY_LIMINE_H

#include <stdint.h>

void validate_boot_protocol(void);

#endif // EARLY_LIMINE_H