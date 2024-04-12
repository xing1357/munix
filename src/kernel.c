#include "kernel.h"
#include "screen.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "pit.h"

void kmain() {
    screen_init(WHITE, BLUE);
    printf("Welcome to SimpleOS!\n");
    gdt_init();
    idt_init();
    pit_init(4);
    asm volatile("sti");
    while(1);
}
