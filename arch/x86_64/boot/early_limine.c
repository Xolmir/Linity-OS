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
#include <panic.h>

__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(6);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request memory_map_request = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

void validate_boot_protocol(void) {

    if (!LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision)) {
        panic("Unsupported Limine base revision");
    }

    if (!memory_map_request.response ||
        memory_map_request.response->entry_count == 0 ||
        !memory_map_request.response->entries) {
        panic("Invalid Limine memory map");
    }
}