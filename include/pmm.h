#ifndef PMM_H
#define PMM_H

#include "types.h"

#define FRAME_SIZE 4096

// Macros for bitmap manipulation
#define SET_BIT(x) bitmap[x / 8] |= (1 << (x % 8))
#define CLEAR_BIT(x) bitmap[x / 8] &= (~(1 << (x % 8)))
#define ISSET(x) ((bitmap[x / 8] >> (x % 8)) & 0x1)

#define BLOCK_ALIGN(addr) (((addr) & 0xFFFFF000) + 0x1000)

void pmm_init(uint32_t mem_size);
uint32_t pmm_alloc_frame();
void pmm_free_frame(int idx);
void pmm_test();

#endif
