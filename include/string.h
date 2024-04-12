#ifndef STRING_H
#define STRING_H

#include "types.h"

void memcpy(void* src, void* dest, uint32_t len);
void memset(void* src, uint8_t data, uint32_t len);

void strcpy(char* src, char* dest, uint32_t len);
int strcmp(const char* s1, const char* s2);
int strlen(const char* s);

void itoa(char *buf, int base, int d);

#endif
