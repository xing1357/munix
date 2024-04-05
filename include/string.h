#ifndef STRING_H
#define STRING_H

#include "types.h"

void memcpy(uint8_t* src, uint8_t* dest, int len);
void memset(uint8_t* src, uint8_t data, int len);

void strcpy(char* src, char* dest, int len);
int strcmp(const char* s1, const char* s2);
int strlen(const char* s);

#endif
