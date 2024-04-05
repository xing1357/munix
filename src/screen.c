#include "screen.h"
#include "vga.h"
#include "string.h"

int cursor_x = 0, cursor_y = 0;

uint16_t* g_vga_buffer;
uint8_t g_fore_color = WHITE, g_back_color = BLACK;

void screen_clear()
{
    for(int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        g_vga_buffer[i] = vga_entry(0, g_fore_color, g_back_color);
    }

    cursor_x = 0;
    cursor_y = 0;
    vga_set_cursor_pos(cursor_x, cursor_y);
}

void screen_scroll()
{
    // Move each line up
    for(int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++)
    {
        g_vga_buffer[i] = g_vga_buffer[i + 80];
    }
}

void screen_put_char(char c)
{
    cursor_x++;

    if(cursor_x > 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    if(cursor_y > 25)
    {
        screen_scroll();
        cursor_y = 25;
    }

    if(c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }

    else
    {
        g_vga_buffer[cursor_y * 80 + cursor_x] = vga_entry(c, g_fore_color, g_back_color);
    }

}

void screen_put_string(char* s)
{
    int len = strlen(s);
    for(int i = 0; i < len; i++)
    {
        screen_put_char(s[i]);
    }
}

void screen_init(uint8_t fore_color, uint8_t back_color)
{
    vga_disable_cursor();
    g_vga_buffer = (uint16_t*)0xB8000;
    g_fore_color = fore_color;
    g_back_color = back_color;

    screen_clear(g_fore_color, g_back_color);
}
