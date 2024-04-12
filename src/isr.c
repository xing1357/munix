#include "isr.h"
#include "idt.h"
#include "screen.h"
#include "pic_8295.h"

interrupt_handler_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, interrupt_handler_t h)
{
    interrupt_handlers[n] = h;
}

void isr_handler(registers_t* regs)
{
    if(interrupt_handlers[regs->int_no])
        interrupt_handlers[regs->int_no](regs);
    else
    {
        printf("Unhandled Interrupt :%d", regs->int_no);
    }
}

void irq_handler(registers_t* regs)
{
    if(interrupt_handlers[regs->int_no] != 0)
        interrupt_handlers[regs->int_no](regs);

    pic8295_EOI(regs->int_no);
}
