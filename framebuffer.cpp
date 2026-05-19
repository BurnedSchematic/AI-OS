#include "framebuffer.h"
#include "mailbox.h"
#include "font.h"

static volatile uint32_t mailbox[36] __attribute__((aligned(16)));

uint32_t width;
uint32_t height;
uint32_t pitch;
uint32_t* framebuffer;

bool framebuffer_init()
{
    mailbox[0] = 35 * 4;
    mailbox[1] = 0;

    mailbox[2] = 0x48003;
    mailbox[3] = 8;
    mailbox[4] = 8;
    mailbox[5] = 640;
    mailbox[6] = 480;

    mailbox[7] = 0x48004;
    mailbox[8] = 8;
    mailbox[9] = 8;
    mailbox[10] = 640;
    mailbox[11] = 480;

    mailbox[12] = 0x48005;
    mailbox[13] = 4;
    mailbox[14] = 4;
    mailbox[15] = 32;

    mailbox[16] = 0x40001;
    mailbox[17] = 8;
    mailbox[18] = 8;
    mailbox[19] = 16;
    mailbox[20] = 0;

    mailbox[21] = 0x40008;
    mailbox[22] = 4;
    mailbox[23] = 4;
    mailbox[24] = 0;

    mailbox[25] = 0;

    if (!Mailbox::call(mailbox, 8))
        return false;

    framebuffer = (uint32_t*)(mailbox[19] & 0x3FFFFFFF);
    pitch = mailbox[24];

    width = 640;
    height = 480;

    return true;
}

uint32_t* get_framebuffer()
{
    return framebuffer;
}

void clear_screen(uint32_t color)
{
    for (uint32_t y = 0; y < height; y++)
    {
        uint32_t row = y * (pitch / 4);

        for (uint32_t x = 0; x < width; x++)
        {
            framebuffer[row + x] = color;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color)
{
    if (x < 0 || x >= width)
    {
        return;
    }

    if (y < 0 || y >= height)
    {
        return;
    }

    framebuffer[y * (pitch / 4) + x] = color;
}

void draw_rect(int x, int y, int w, int h, uint32_t color)
{
    for (int py = y; py < y + h; py++)
    {
        for (int px = x; px < x + w; px++)
        {
            draw_pixel(px, py, color);
        }
    }
}

void draw_char(int px, int py, char c, uint32_t color)
{
    const uint8_t* glyph;

    if (c == ' ')
    {
        glyph = font8x8[0];
    }
    else if (c >= '0' && c <= '9')
    {
        glyph = font8x8[1 + (c - '0')];
    }
    else if (c >= 'A' && c <= 'Z')
    {
        glyph = font8x8[11 + (c - 'A')];
    }
    else
    {
        return;
    }

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (glyph[y] & (1 << (7 - x)))
            {
                draw_pixel(
                    px + x,
                    py + y,
                    color
                );
            }
        }
    }
}

void draw_string(int x, int y, const char* s, uint32_t color)
{
    while (*s)
    {
        draw_char(x, y, *s, color);
        x += 8;
        s++;
    }
}