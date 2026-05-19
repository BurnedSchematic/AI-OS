#include "framebuffer.h"
#include "graphics.h"
#include "dwc2.h"

extern "C" void kernel_main()
{
    framebuffer_init();

    clear_screen(0x00000000);

    draw_char(
        'A',
        100,
        100,
        0x00FFFFFF
    );

    while (1)
    {
    }
}