#include "pit.h"
#include "isr.h"
#include "screen.h"
#include "ports.h"

int ticks = 0;

void pit_callback(registers_t* regs)
{
    ticks++;

    //printf("Tick: %d\n", ticks);
}

void pit_init(uint32_t hz)
{
    int div = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, div & 0xFF);
    outb(0x40, (div >> 8) & 0xFF);

    register_interrupt_handler(IRQ0, &pit_callback);
}



