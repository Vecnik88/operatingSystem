#include <AOS-unix/isr.h>

isr_t interrupt_handlers[256];

void isr_handler(registers_t regs)
{
	printk("received interrupt: %d\n", regs.int_no);
}

void irq_handler(registers_t regs)
{
	if (regs.int_no >= 40) {
		out_byte(0xA0, 0x20);
	}
	printk("I run");

	out_byte(0x20, 0x20);
	if (interrupt_handlers[regs.int_no] != 0) {
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
	interrupt_handlers[n] = handler;
	printk("register_interrupt_handler run");
}