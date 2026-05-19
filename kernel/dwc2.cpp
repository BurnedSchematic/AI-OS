#include "dwc2.h"

#define USB_BASE 0x3F980000

#define GAHBCFG   ((volatile uint32_t*)(USB_BASE + 0x008))
#define GUSBCFG   ((volatile uint32_t*)(USB_BASE + 0x00C))
#define GRSTCTL   ((volatile uint32_t*)(USB_BASE + 0x010))
#define GINTSTS   ((volatile uint32_t*)(USB_BASE + 0x014))
#define GINTMSK   ((volatile uint32_t*)(USB_BASE + 0x018))
#define HPRT      ((volatile uint32_t*)(USB_BASE + 0x440))
#define HCFG      ((volatile uint32_t*)(USB_BASE + 0x400))

static void delay(int count)
{
    while (count--)
    {
        asm volatile("nop");
    }
}

bool usb_init()
{
    // Core soft reset

    *GRSTCTL |= (1 << 0);

    int timeout = 1000000;

    while ((*GRSTCTL & (1 << 0)) && timeout--)
    {
    }

    if (timeout <= 0)
    {
        return false;
    }

    delay(100000);

    // Enable DMA + global interrupts

    *GAHBCFG |= 1;

    // Force host mode

    *GUSBCFG |= (1 << 29);

    delay(100000);

    // Full-speed PHY clock

    *HCFG = 1;

    delay(100000);

    // Power port

    *HPRT |= (1 << 12);

    delay(500000);

    return true;
}

bool usb_device_connected()
{
    uint32_t port =
        *HPRT;

    return (port & (1 << 0));
}

uint32_t usb_get_hprt()
{
    return *HPRT;
}
