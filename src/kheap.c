#include "kheap.h"


void* kmalloc_a(uint32_t size) {
    void* ret = temp_mem;
    ret = (void*)PAGE_ALIGN(ret);
    temp_mem = temp_mem + size;
    return ret;
}