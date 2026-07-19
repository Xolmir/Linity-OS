// SPDX-License-Identifier: GPL-3.0

/*
 * printk.c 
 *   Kernel printing functions
 *
 * Maintained by: 
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 */

#include <printk.h>
#include <kstatus.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <hal/hal_console.h>

static const char digits[] = "0123456789";
static const char hex_digits_lower[] = "0123456789abcdef";
static const char hex_digits_upper[] = "0123456789ABCDEF";

enum {
    LEN_DEFAULT,
    LEN_LONG,
    LEN_LONGLONG,
    LEN_SIZE
};

static void kputc(char c) {
    switch (kernel_state) {
        case KSTATUS_EARLY:
            early_arch_debug_putc(c);
            break;

        case KSTATUS_EARLY_PANIC:
            early_arch_debug_putc(c);
            break;
        
        case KSTATUS_RUNNING:
            //stdout_device->putc(c);
            break;

        case KSTATUS_PANIC:
            //stdout_device->putc(c);
            break;
        default:
            early_arch_debug_putc(c);
            break;
    }
}

static void kput_uint_base(uint64_t value, uint32_t base, const char* digits) {
    if (value == 0) {
        kputc('0');
        return;
    }
    char buffer[32];
    int index = 0;
    while (value > 0) {
        buffer[index++] = digits[value % base];
        value /= base;
    }
    while (--index >= 0) {
        kputc(buffer[index]);
    }
}

static int64_t va_int(va_list ap, int len) {
    if (len == LEN_LONGLONG) return va_arg(ap, long long);
    if (len == LEN_LONG) return va_arg(ap, long);
    return (int32_t)va_arg(ap, int);
}

static uint64_t va_uint(va_list ap, int len) {
    if (len == LEN_LONGLONG) return va_arg(ap, unsigned long long);
    if (len == LEN_LONG) return va_arg(ap, unsigned long);
    return va_arg(ap, unsigned int);
}

void printk(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintk(format, args);
    va_end(args);
}

void vprintk(const char* format, va_list args) {
    int length = LEN_DEFAULT;

    const char* fmt = format ? format : "(null)";
    for (const char* ptr = fmt; *ptr != '\0'; ptr++) {
        if (*ptr == '%') {
            ptr++;
            length = LEN_DEFAULT;
            if (*ptr == 'l') {
                length = LEN_LONG;
                ptr++;
                if (*ptr == 'l') {
                    length = LEN_LONGLONG;
                    ptr++;
                }
            }
            if (*ptr == '\0') { kputc('%'); break; }
            switch (*ptr) {
                case 'c': {
                    char c = (char)va_arg(args, int);
                    kputc(c);
                    break;
                }
                case 's': {
                    const char* str = va_arg(args, const char*);
                    if (!str) str = "(null)";
                    while (*str)
                        kputc(*str++);
                    break;
                }
                case 'd':
                case 'i': {
                    int64_t dec = va_int(args, length);
                    if (dec < 0) {
                        kputc('-');
                        kput_uint_base(((uint64_t)(~(uint64_t)dec)) + 1, 10, digits);
                    } else {
                        kput_uint_base((uint64_t)dec, 10, digits);
                    }
                    break;
                }
                case 'u': {
                    kput_uint_base(va_uint(args, length), 10, digits);
                    break;
                }
                case 'o': {
                    kput_uint_base(va_uint(args, length), 8, digits);
                    break;
                }
                case 'x': {
                    kput_uint_base(va_uint(args, length), 16, hex_digits_lower);
                    break;
                }
                case 'X': {
                    kput_uint_base(va_uint(args, length), 16, hex_digits_upper);
                    break;
                }
                case 'p': {
                    void* pointer = va_arg(args, void*);
                    kputc('0');
                    kputc('x');
                    kput_uint_base((uintptr_t)pointer, 16, hex_digits_lower);
                    break;
                }
                case '%': {
                    kputc('%');
                    break;
                }
                default: {
                    kputc('%');
                    kputc(*ptr);
                    break;
                }
            }
        }
        else {
            kputc(*ptr);
        }
    }
}