#include "vga.h"
#include "ports.h"

void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    outb(0x0A, 0x3D4);
    outb((inb(0x3D5) & 0xC0) | cursor_start, 0x3D5);

    outb(0x0B, 0x3D4);
    outb(((inb(0x3D5)) & 0xE0) | cursor_end, 0x3D5);
}

void vga_disable_cursor()
{
    outb(0x0A, 0x3D4);
    outb(0x20, 0x3D5);
}

void vga_set_cursor_pos(int x, int y)
{
    uint16_t pos = y * VGA_WIDTH + x;

    outb(0x0F, 0x3D4);
    outb((uint8_t)(pos & 0xFF), 0x3D5);
    outb(0x0E, 0x3D4);
    outb((uint8_t)((pos >> 8) & 0xFF), 0x3D5);
}

uint16_t vga_get_cursor_pos()
{
    uint16_t pos = 0;
    outb(0x0F, 0x3D4);
    pos |= inb(0x3D5);
    outb(0x0E, 0x3D4);
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
