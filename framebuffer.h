#pragma once

#include <stdint.h>

extern uint32_t width;
extern uint32_t height;
extern uint32_t pitch;
extern uint32_t* framebuffer;

bool framebuffer_init();

uint32_t* get_framebuffer();

void draw_pixel(int x, int y, uint32_t color);

void clear_screen(uint32_t color);

void draw_rect(int x, int y, int w, int h, uint32_t color);

void draw_hex(int x, int y, uint32_t value, uint32_t color);

void draw_char(int x, int y, char c, uint32_t color);

void draw_string(int x, int y, const char* s, uint32_t color);