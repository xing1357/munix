#ifndef VGA_H
#define VGA_H

#include "types.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum VGA_COLOR
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void vga_disable_cursor();
void vga_set_cursor_pos(int x, int y);
uint16_t vga_get_cursor_pos();

uint16_t vga_entry(uint8_t c, uint8_t forecolor, uint8_t backcolor);

#endif
