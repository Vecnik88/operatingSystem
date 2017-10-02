#include "timer.h"
#include "ports.h"
#include "../libc/function.h"
#include "isr.h"

u32_int tick = 0;

static void timer_callback(registers_t regs)
{
	tick++;
	UNUSED(regs);
}

void init_timer(u32_int freq)
{
	register_interrupt_handler(IRQ0, timer_callback);

	u32_int divisor = 1193180/freq;
	u8_int low = (u8_int)(divisor & 0xff);
	u8_int high = (u8_int)((divisor >> 8) & 0xff);

	out_byte(0x43, 0x36);
	out_byte(0x40, low);
	out_byte(0x40, high);
}