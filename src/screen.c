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
    // Clear the top line
    memset(g_vga_buffer, 0, 80);

    // Move each line up
    for(int i = 80; i < (VGA_HEIGHT) * VGA_WIDTH; i++)
    {
        g_vga_buffer[i - 80] = g_vga_buffer[i];
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
        cursor_y = 24;
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

void printf(const char *format, ...)
{
    char **arg = (char **)&format;
    int c;
    char buf[32];

    arg++;

    memset(buf, 0, sizeof(buf));
    while ((c = *format++) != 0) {
        if (c != '%')
            screen_put_char(c);
        else {
            char *p, *p2;
            int pad0 = 0, pad = 0;

            c = *format++;
            if (c == '0') {
                pad0 = 1;
                c = *format++;
            }

            if (c >= '0' && c <= '9') {
                pad = c - '0';
                c = *format++;
            }

            switch (c) {
                case 'd':
                case 'u':
                case 'x':
                    itoa(buf, c, *((int *)arg++));
                    p = buf;
                    goto string;
                    break;

                case 's':
                    p = *arg++;
                    if (!p)
                        p = "(null)";

                string:
                for (p2 = p; *p2; p2++)
                    ;
                for (; p2 < p + pad; p2++)
                    screen_put_char(pad0 ? '0' : ' ');
                while (*p)
                    screen_put_char(*p++);
                break;

                default:
                    screen_put_char(*((int *)arg++));
                    break;
            }
        }
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
