// SPDX-License-Identifier: GPL-3.0

/*
 * early_serial.c
 *   Early serial port initialization and output for early debugging
 *
 * Maintained by:
 *   Xolmir (İsmail Efe Telli) <xolmir@proton.me>
 *
 * References:
 *   https://wiki.osdev.org/Serial_Ports
 *   https://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming#UART_Registers
 */

#include <stdint.h>
#include <stddef.h>
#include <boot/early_serial.h>
#include <io.h>

#define EARLY_UART_COM1 0x3F8

// DLAB 0
#define EARLY_UART_THR  (EARLY_UART_COM1 + 0)
#define EARLY_UART_RBR  (EARLY_UART_COM1 + 0)
#define EARLY_UART_IER  (EARLY_UART_COM1 + 1)

// DLAB 1
#define EARLY_UART_DLL  (EARLY_UART_COM1 + 0)
#define EARLY_UART_DLH  (EARLY_UART_COM1 + 1)

// Not affected by DLAB
#define EARLY_UART_IIR  (EARLY_UART_COM1 + 2)
#define EARLY_UART_FCR  (EARLY_UART_COM1 + 2)
#define EARLY_UART_LCR  (EARLY_UART_COM1 + 3)
#define EARLY_UART_MCR  (EARLY_UART_COM1 + 4)
#define EARLY_UART_LSR  (EARLY_UART_COM1 + 5)
#define EARLY_UART_MSR  (EARLY_UART_COM1 + 6)
#define EARLY_UART_SCR  (EARLY_UART_COM1 + 7)

#define EARLY_UART_LSR_THRE (1 << 5)
#define EARLY_UART_LSR_DR   (1 << 0)

#define EARLY_UART_LCR_DLAB (1 << 7)
#define EARLY_UART_LCR_8N1  (3 << 0)

#define EARLY_UART_FCR_TRIG_14  (3 << 6)
#define EARLY_UART_FCR_CLR_TX   (1 << 2)
#define EARLY_UART_FCR_CLR_RX   (1 << 1)
#define EARLY_UART_FCR_ENABLE   (1 << 0)

#define EARLY_UART_MCR_LOOP (1 << 4)
#define EARLY_UART_MCR_RTS  (1 << 1)
#define EARLY_UART_MCR_DTR  (1 << 0)

static int early_serial_ready = 0;

static int is_transmit_empty(void) {
    return inb(EARLY_UART_LSR) & EARLY_UART_LSR_THRE;
}

static int is_data_ready(void) {
    return inb(EARLY_UART_LSR) & EARLY_UART_LSR_DR;
}

int early_init_serial(void) {
    early_serial_ready = 0;
    outb(EARLY_UART_IER, 0x00);
    outb(EARLY_UART_LCR, EARLY_UART_LCR_DLAB);
    outb(EARLY_UART_DLL, 0x03);
    outb(EARLY_UART_DLH, 0x00);
    outb(EARLY_UART_LCR, EARLY_UART_LCR_8N1);
    outb(EARLY_UART_FCR,
        EARLY_UART_FCR_TRIG_14  |
        EARLY_UART_FCR_CLR_TX   |
        EARLY_UART_FCR_CLR_RX   |
        EARLY_UART_FCR_ENABLE
    );
    outb(EARLY_UART_MCR,
        EARLY_UART_MCR_LOOP |
        EARLY_UART_MCR_RTS  |
        EARLY_UART_MCR_DTR
    );
    outb(EARLY_UART_THR, 0x10);

    uint32_t timeout = 1000000;
    while (!is_data_ready()) {
        if (--timeout == 0) {
            outb(EARLY_UART_MCR, 0x00);
            return 1;
        }
    }

    if (inb(EARLY_UART_RBR) != 0x10) {
        outb(EARLY_UART_MCR, 0x00);
        return 1;
    }
    outb(EARLY_UART_MCR,
        EARLY_UART_MCR_RTS  |
        EARLY_UART_MCR_DTR
    );
    early_serial_ready = 1;
    return 0;
}

void early_serial_write_char(char character) {
    if (!early_serial_ready) {
        return;
    }
    while (!is_transmit_empty()) {
        __asm__ volatile ("pause");
    }

    outb(EARLY_UART_THR, character);
}