#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

#define LOAD_MEMORY_ADDRESS 0xC0000000
#define K 1024
#define M (1024*K)
#define G (1024*M)

// symbols from linker.ld for section addresses
extern uint32_t end;

#endif
