#include "panic.h"
#include "screen.h"

void panic(const char* msg, const char* file, uint32_t line) {
    printf("\nPanic! System Halting!\nIn: %s, at line %d", msg, file, line);
    asm volatile("hlt");
}
