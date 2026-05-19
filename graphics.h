#pragma once

#include <stdint.h>
#include "frame.h"

extern Frame backbuffer;

void graphics_init();

void swap_buffers();

void draw_pixel_frame(Frame* frame, int x, int y, uint32_t color);

void draw_rect_frame(Frame* frame, int x, int y, int w, int h, uint32_t color);

void clear_frame(Frame* frame, uint32_t color);

void blit_frame(Frame* src);

void draw_hex(uint32_t value,
    int x,
    int y,
    uint32_t color);