#ifndef PAGING_H
#define PAGING_H

#include "types.h"

#define EMPTY_TAB 0x00000002 // Kernel mode, write enabled, and not present
#define PAGE_SIZE 4096

// There are some small differences actually in page directory and page table entries
// But for simplicity sake lets assume they are the same
typedef struct page_t {
    uint32_t present: 1;
    uint32_t rw: 1;
    uint32_t user: 1;
    uint32_t accessed: 1;
    uint32_t dirty: 1;
    uint32_t unused: 7;
    uint32_t frame: 20;
} page_t;

typedef struct page_table_t {
    page_t pages[1024];
} page_table_t;

typedef struct page_dir_t {
    page_table_t* tables[1024]; // Array of pointers to all the page tables
    page_t tables_phys[1024]; // The actual physical location of tables
    uint32_t phys_addr; // Physical location of the page directory
} page_dir_t;

void paging_init();

#endif
