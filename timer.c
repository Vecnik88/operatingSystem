#include "timer.h"
#include "../drivers/monitor.h"
#include "../kernel/util.h"
#include "isr.h"

u32_int tick = 0;

static void timer_callback(register_t regs)
{
	tick++;
	k_print("Tick: ");

	s8_int tick_ascii[256];
	i_t_o_a(tick, tick_ascii);
	k_print(tick_ascii);
	k_print("\n");
}

void init_timer(u32_int freq)
{
	register_interrupt_handler(IRQ0, timer_callback);

	u32_int divisor = 1193180/freq;
	u8_int low = (u8_int)(divisor & 0xff);
	u8_int high = (u8_int)((divisor >> 8) & 0xff);

	out_byte(0x43, 0x36);
	out_byte(0x40, low);
	out_byte(ox40, high);
}