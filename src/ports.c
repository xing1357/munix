#include "ports.h"

uint8_t inb(uint16_t port)
{
    uint8_t v;
    asm volatile("inb %1, %0" : "=a"(v) : "Nd"(port));

    return v;
}

uint16_t inw(uint16_t port)
{
    uint16_t v;
    asm volatile("inw %1, %0": "=a"(v) : "dN"(port));

    return v;
}

uint32_t inl(uint16_t port)
{
    uint32_t v;
    asm volatile ("inl %%dx, %%eax" : "=a" (v) : "dN" (port));

    return v;
}

void outb(uint16_t port, uint8_t data)
{
    asm volatile("outb %1, %0" :: "dN"(port), "a"(data));
}

void outw(uint16_t port, uint16_t data)
{
    asm volatile ("outw %1, %0" : : "dN" (port), "a" (data));
}
void outl(uint16_t port, uint32_t data)
{
    asm volatile ("outl %%eax, %%dx" : : "dN" (port), "a" (data));
}

