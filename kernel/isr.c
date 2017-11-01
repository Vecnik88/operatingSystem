#include <AOS-unix/isr.h>
#include <AOS-unix/printk.h>

void isr_handler(registers_t regs)
{
	printk("received interrupt: %d\n", regs.int_no);
}