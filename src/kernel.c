#include "kernel.h"
#include "screen.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "pit.h"
#include "multiboot.h"
#include "pmm.h"
#include "panic.h"
#include "paging.h"

void kmain(multiboot_info_t * mb_info) {
    screen_init(WHITE, BLUE);
    printf("Welcome to SimpleOS!\n");
    gdt_init();
    idt_init();
    pit_init(4);
    pmm_init(1096 * M); // Yeah, lazy much? I'll calculate actual memory size later. Lets pretend we have ~40mb. qemu gives about 128 MiB but i'm not too sure
    paging_init();
    asm volatile("sti");

    printf("\nGenerating page fault:-\n");
    int *x = (int *)0x8973456;
    x[0] = 12345;

    //pmm_test();


}
