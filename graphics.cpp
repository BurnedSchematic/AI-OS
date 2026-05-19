#include "graphics.h"
#include "framebuffer.h"
#include "frame.h"

static uint32_t backbuffer_memory[640 * 480];

Frame backbuffer =
{
	640,
	480,
	640 * 4,
	backbuffer_memory
};

void draw_pixel_frame(Frame* frame,
	int x,
	int y,
	uint32_t color)
{
	if (x < 0 || x >= (int)frame->width)
	{
		return;
	}

	if (y < 0 || y >= (int)frame->height)
	{
		return;
	}

	frame->pixels[
		y * (frame->pitch / 4) + x
	] = color;
}

void swap_buffers()
{
	uint32_t* framebuffer =
		get_framebuffer();

	uint32_t fb_pitch =
		pitch / 4;

	for (uint32_t y = 0; y < height; y++)
	{
		for (uint32_t x = 0; x < width; x++)
		{
			framebuffer[
				y * fb_pitch + x
			] =
				backbuffer.pixels[
					y * backbuffer.width + x
				];
		}
	}
}

void clear_frame(Frame* frame,
	uint32_t color)
{
	uint32_t pitch_pixels =
		frame->pitch / 4;

	for (uint32_t y = 0; y < frame->height; y++)
	{
		uint32_t row =
			y * pitch_pixels;

		for (uint32_t x = 0; x < frame->width; x++)
		{
			frame->pixels[row + x] = color;
		}
	}
}

void draw_rect_frame(Frame* frame,
	int x,
	int y,
	int w,
	int h,
	uint32_t color)
{
	for (int py = y; py < y + h; py++)
	{
		for (int px = x; px < x + w; px++)
		{
			draw_pixel_frame(
				frame,
				px,
				py,
				color
			);
		}
	}
}

void blit_frame(Frame* src)
{
	uint32_t* framebuffer =
		get_framebuffer();

	uint32_t fb_pitch = 
		pitch / 4;

	uint32_t src_pitch =
		src->pitch / 4;

	for (uint32_t y = 0; y < src->height; y++)
	{
		for (uint32_t x = 0; x < src->width; x++)
		{
			framebuffer[
				y * fb_pitch + x
			] =
			src->pixels[
				y * src_pitch + x
			];
		}
	}
}

void draw_hex(uint32_t value,
	int x,
	int y,
	uint32_t color)
{
	const char* hex =
		"0123456789ABCDEF";

	for (int i = 0; i < 8; i++)
	{
		char c =
			hex[(value >> ((7 - i) * 4)) & 0xF];

		draw_char(c,
			x + i * 8,
			y,
			color);
	}
}