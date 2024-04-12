#ifndef ISR_H
#define ISR_H

#include "types.h"
#include "idt.h"

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

void register_interrupt_handler(uint8_t n, interrupt_handler_t h);
void isr_handler(registers_t* regs);

#endif
