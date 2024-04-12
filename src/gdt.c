#include "gdt.h"

#define GDT_NUM_ENTRIES 5

gdt_entry_t GDT[GDT_NUM_ENTRIES];
gdt_ptr_t gdt_ptr;

extern void gdt_flush (uint32_t);
static void gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

void gdt_init()
{
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_NUM_ENTRIES - 1;
    gdt_ptr.base = (uint32_t) &GDT;

    gdt_entry(0, 0, 0, 0, 0);             // Null Segment
    gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xCF); // Kernel Mode Code Segment
    gdt_entry(2, 0, 0xFFFFF, 0x92, 0xCF); // Kernel Mode Data Segment
    gdt_entry(3, 0, 0xFFFFF, 0xFA, 0xCF); // User Mode Code Segment
    gdt_entry(4, 0, 0xFFFFF, 0xF2, 0xCF); // User Mode Data Segment

    gdt_flush((uint32_t)&gdt_ptr);
}

static void gdt_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    GDT[num].base_low = (base & 0xFFFF);
    GDT[num].base_middle = (base >> 16) & 0xFF;
    GDT[num].base_high = (base >> 24) & 0xFF;

    GDT[num].limit_low = limit & 0xFFFF;
    GDT[num].granularity = (limit >> 16) & 0x0F;

    GDT[num].granularity |= (granularity & 0xF0);
    GDT[num].access = access;
}

