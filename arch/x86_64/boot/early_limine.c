// SPDX-License-Identifier: GPL-3.0

/*
 * early_limine.c 
 *   Early Limine request handling
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References: 
 *   https://wiki.osdev.org/Limine_Bare_Bones
 *   https://github.com/Limine-Bootloader/Limine/blob/v12.x/USAGE.md
 */

#include <limine.h>
#include <boot/early_limine.h>
#include <stdint.h>

__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

void check_limine(void) {
    __asm__ volatile ("cli");

    // Check if Limine base revision isn't supported halt CPU
    if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == 0) {
        while(1) {
            __asm__ volatile ("hlt");
        }
    }
    // Check if Limine framebuffer request isn't success halt CPU
    if (framebuffer_request.response == 0 || framebuffer_request.response->framebuffer_count < 1) {
        while(1) {
            __asm__ volatile ("hlt");
        }
    }
}