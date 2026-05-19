#pragma once

#include <stdint.h>

bool usb_init();

bool usb_device_connected();

uint32_t usb_get_hprt();