#ifndef PANIC_H
#define PANIC_H

#include "types.h"

#define PANIC(msg) panic(msg, __FILE__, __LINE__);

void panic(const char* msg, const char* file, uint32_t line);

#endif
