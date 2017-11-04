#include <AOS-unix/keyboard.h>
#include <AOS-unix/printk.h>

static void keyboard_callback(registers_t regs)
{
	uint8_t asc = in_byte(0x60);

	printk("keyboard signal on\n");
}

void init_keyboard()
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}