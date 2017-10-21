#include "timer.h"

u32_int tick = 0;

static void timer_callback(registers_t reg)
{
	++tick;
	screen_write("Tick: ");
	screen_write_dec(tick);
    add_screen_char('\n');
}

void init_timer(u32_int frequency)
{
    /* регистрируем наш callback */
    register_interrupt_handler(IRQ0, &timer_callback);

    /* 	
     * значение, которое мы посылаем в PIT, является значением, 
     * на которое будет делиться основная частота
	 * (1193180 Hz) для того, чтобы получить необходимую нам частоту. 
	 * Важно отметить, что делитель должен быть достаточно маленьким с тем, 
	 * чтобы уместиться в 16 битов разрядной сетки.
     */
    u32_int div = 1193180 / frequency;

    /* отправляем байт команды */
    out_byte(0x43, 0x36);

    /* делитель должен посылаться побайтно, так что мы делим его на старший и младший байты. */
    u8_int low = (u8_int)(div & 0xFF);
    u8_int high = (u8_int)( (div >> 8) & 0xFF );

    /* отправляем делитель частоты */
    out_byte(0x40, low);
    out_byte(0x40, high);
}