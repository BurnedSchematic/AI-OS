#pragma once

#include <stdint.h>

struct Frame
{
	uint32_t width;
	uint32_t height;
	uint32_t pitch;

	uint32_t* pixels;
};