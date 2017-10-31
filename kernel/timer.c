#include <AOS-unix/timer.h>

uint32_t tick = 0;

static void timer_callback(registers_t regs)
{
	tick++;
	printk("Tick: %d\n", tick);
}

void init_timer(uint32_t frequency)
{
	register_interrupt_handler(IRQ0, &timer_callback);
	uint32_t divisor = 1193180/frequency;
	out_byte(0x43, 0x36);

	uint8_t low = (uint8_t)(divisor & 0xFF);
	uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

	/* посылаем делитель частоты */
	out_byte(0x40, low);
	out_byte(0x40, high);
}