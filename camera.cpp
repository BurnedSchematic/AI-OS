#include "camera.h"
#include "memory.h"

static uint32_t* camera_pixels;

Frame camera_frame;

bool camera_init()
{
	camera_pixels =
		(uint32_t*)alloc_aligned(
			640 * 480 * 4,
			4096
		);

	if (!camera_pixels)
	{
		return false;
	}

	camera_frame.width = 640;
	camera_frame.height = 480;
	camera_frame.pitch = 640 * 4;
	camera_frame.pixels = camera_pixels;

	return true;
}