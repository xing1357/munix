#include "vga.h"
#include "ports.h"

void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, ((inb(0x3D5)) & 0xE0) | cursor_end);
}

void vga_disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void vga_set_cursor_pos(int x, int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

uint16_t vga_get_cursor_pos()
{
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}

uint16_t vga_entry(uint8_t c, uint8_t forecolor, uint8_t backcolor)
{
    uint16_t ax = 0;
    uint8_t ah = 0, al = 0;

    ah = backcolor;
    ah <<= 4;
    ah |= forecolor;
    ax = ah;
    ax <<= 8;
    al = c;
    ax |= al;

    return ax;

}
