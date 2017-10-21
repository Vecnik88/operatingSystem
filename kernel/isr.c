#include "isr.h"

isr_t interrupt_handlers[256];

void register_interrupt_handler(u8_int n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs)
{
    screen_write("recieved interrupt: ");
    screen_write_hex(regs.int_no);
    screen_write("\n");
}

void irq_handler(registers_t regs)
{
    if (regs.int_no >= 40)
    {
        out_byte(0xA0, 0x20);
    }

    out_byte(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }

}
