#include <AOS-unix/isr.h>

void isr_handler(registers_t regs)
{
	printk("hello\n");
	//printk("received interrupt: %d\n", regs.int_no);
}