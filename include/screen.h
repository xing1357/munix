#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

void screen_clear();
void screen_init(uint8_t fore_color, uint8_t back_color);
void screen_put_string(char* s);
void printf(const char *format, ...);

#endif
