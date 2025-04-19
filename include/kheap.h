#ifndef KHEAP_H
#define KHEAP_H

#include "types.h"

#define IS_ALIGN(addr) ((((uint32_t)(addr)) | 0xFFFFF000) == 0)
#define PAGE_ALIGN(addr) ((((uint32_t)(addr)) & 0xFFFFF000) + 0x1000)

extern uint8_t* bitmap;
extern uint32_t bitmap_size;
extern uint8_t* temp_mem; // Defined in paging.c

void* kmalloc_a(uint32_t size);

#endif