#include "../drivers/ports.h"
#include "../drivers/monitor.h"

/* start kernel */
void main(void)
{
 	clear_screen();
 	isr_init();

    asm volatile("sti");
    init_timer(50);
    /* Comment out the timer IRQ handler to read
     * the keyboard IRQs easier */
    init_keyboard();

    /* Comment out the timer IRQ handler to read
     * the keyboard IRQs easier 

    k_print_at("X", 1, 6);
    k_print_at("This text spans multiple lines", 75, 10);
    k_print_at("There is a line\nbreak", 0, 20);
    k_print("There is a line\nbreak");
    k_print_at("What happens when we run out of space?", 45, 24);
    isr_init();
    // Test the interrupts 
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
    __asm__ __volatile__("int $4");
    __asm__ __volatile__("int $5");
    __asm__ __volatile__("int $6");
    __asm__ __volatile__("int $7");
    __asm__ __volatile__("int $8");
    __asm__ __volatile__("int $9");*/
}