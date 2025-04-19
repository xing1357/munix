#include "paging.h"
#include "kheap.h"
#include "string.h"
#include "pmm.h"
#include "isr.h"
#include "screen.h"
#include "kernel.h"

// Add some assembly abstractions to clean up the code

page_dir_t* kernel_dir;

uint8_t * temp_mem;

// Function to convert virtual address to physical (assuming higher-half kernel)
void* virt_to_phys(void* va) {
    return (void*)(va - LOAD_MEMORY_ADDRESS);
}

page_table_t* get_cr3() {
    uint32_t cr3;
    asm volatile ("movl %%cr3, %%eax" : "=a" (cr3));
    return (page_table_t*)cr3;
}

uint32_t get_cr0() {
    uint32_t cr0;
    asm volatile("movl %%cr0, %%eax" : "=a" (cr0));
    return cr0;
}

void set_cr3(page_dir_t* dir) {
    uint32_t addr = (uint32_t) &dir->tables[0];
    asm volatile("movl %%eax, %%cr3" :: "a"(addr));
}

void set_cr0(uint32_t val) {
    asm volatile("movl %%eax, %%cr0" :: "a"(val));
}

void switch_page_dir(page_dir_t* dir) {
    set_cr3(dir);
    set_cr0(get_cr0() | 0x80000000);
}

void page_alloc(page_dir_t* dir, uint32_t va) {
    uint32_t pd_idx = va >> 22;
    uint32_t pt_idx = va >> 12 & 0x3FF;

    page_table_t* table = dir->tables[pd_idx];

    // If the table doesn't exist, allocate a new one
    if(!table) {
        table = kmalloc_a(sizeof(page_table_t));
        memset(table, 0, sizeof(page_table_t));

        uint32_t phys_table = virt_to_phys((uint32_t)table);
        dir->tables_phys[pd_idx].frame = phys_table >> 12;
        dir->tables_phys[pd_idx].present = 1;
        dir->tables_phys[pd_idx].rw = 1;
        dir->tables_phys[pd_idx].user = 1;

        dir->tables[pd_idx] = table;
    }

    // If the page doesn't exist, call pmm_alloc_frame() to allocate a new one
    if(!table->pages[pt_idx].present) {
        table->pages[pt_idx].frame = pmm_alloc_frame();
        table->pages[pt_idx].present = 1;
        table->pages[pt_idx].rw = 1;
        table->pages[pt_idx].user = 1;
    }
}

void page_fault() {
    printf("Page fault happened ig\n");
}

void paging_init() { 
    // Place the paging data after pmm bitmap
    temp_mem = bitmap + bitmap_size;

    kernel_dir = kmalloc_a(sizeof(page_dir_t));
    memset(kernel_dir, 0, sizeof(page_dir_t)); // This is where pagefault (interrupt 14) happens?

    uint32_t i = LOAD_MEMORY_ADDRESS;
    while(i < LOAD_MEMORY_ADDRESS + 4 * M) {
        page_alloc(kernel_dir, i);
        i = i + PAGE_SIZE;
    }
    
    register_interrupt_handler(14, page_fault);
    switch_page_dir(kernel_dir);
}





