#include <AOS-unix/timer.h>
#include <AOS-unix/isr.h>
#include <AOS-unix/printk.h>
#include <AOS-unix/port.h>

unsigned int tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    printk("Tick: ");
}

void init_timer(unsigned int freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    unsigned int divisor = 1193180 / freq;
    unsigned char low  = (unsigned char)(divisor & 0xFF);
    unsigned char high = (unsigned char)( (divisor >> 8) & 0xFF);
    /* Send the command */
    out_byte(0x43, 0x36); /* Command port */
    out_byte(0x40, low);
    out_byte(0x40, high);
}