#include "uart.h"
#include <stdint.h>

#define MMIO_BASE 0x3F000000

#define GPFSEL1     ((volatile unsigned int*)(MMIO_BASE + 0x200004))
#define GPPUD       ((volatile unsigned int*)(MMIO_BASE + 0x200094))
#define GPPUDCLK0   ((volatile unsigned int*)(MMIO_BASE + 0x200098))

#define UART0_DR    ((volatile unsigned int*)(MMIO_BASE + 0x201000))
#define UART0_FR    ((volatile unsigned int*)(MMIO_BASE + 0x201018))
#define UART0_IBRD  ((volatile unsigned int*)(MMIO_BASE + 0x201024))
#define UART0_FBRD  ((volatile unsigned int*)(MMIO_BASE + 0x201028))
#define UART0_LCRH  ((volatile unsigned int*)(MMIO_BASE + 0x20102C))
#define UART0_CR    ((volatile unsigned int*)(MMIO_BASE + 0x201030))
#define UART0_IMSC  ((volatile unsigned int*)(MMIO_BASE + 0x201038))
#define UART0_ICR   ((volatile unsigned int*)(MMIO_BASE + 0x201044))

static void delay(uint32_t count)
{
    while (count--)
    {
        asm volatile("nop");
    }
}

void uart_init()
{
    *UART0_CR = 0x00000000;

    *GPFSEL1 &= ~((7 << 12) | (7 << 15));
    *GPFSEL1 |= (4 << 12) | (4 << 15);

    *GPPUD = 0;
    delay(150);

    *GPPUDCLK0 = (1 << 14) | (1 << 15);
    delay(150);

    *GPPUDCLK0 = 0;

    *UART0_ICR = 0x7FF;

    *UART0_IBRD = 1;
    *UART0_FBRD = 40;

    *UART0_LCRH = (1 << 4) | (1 << 5) | (1 << 6);

    *UART0_CR = (1 << 0) | (1 << 8) | (1 << 9);
}

void uart_putc(char c)
{
    while (*UART0_FR & (1 << 5));

    *UART0_DR = c;
}

void uart_puts(const char* str)
{
    while (*str)
    {
        uart_putc(*str++);
    }
}