#ifndef PORTS_H
#define PORTS_H

#include "types.h"

uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

void outb(uint8_t data, uint16_t port);
void outw(uint16_t data, uint16_t port);
void outl(uint32_t data, uint16_t port);

#endif
