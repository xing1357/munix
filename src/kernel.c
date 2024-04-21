#include "kernel.h"
#include "screen.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "pit.h"
#include "multiboot.h"
#include "pmm.h"
#include "panic.h"

void kmain(unsigned long magic, unsigned long addr, struct multiboot_info *mboot_info) {
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC)
        printf("invalid magic number!");

    screen_init(WHITE, BLUE);
    printf("Welcome to SimpleOS!\n");
    gdt_init();
    idt_init();
    pit_init(4);
    asm volatile("sti");


    pmm_init(40000000); // Yeah, lazy much? I'll calculate actual memory size later. Lets pretend we have ~40mb. qemu gives about 128 MiB but i'm not too sure
    //pmm_test();


}
