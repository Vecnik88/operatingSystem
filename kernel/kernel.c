#include "../cpu/isr.h"
#include "../drivers/monitor.h"
#include "kernel.h"
#include "../libc/string.h"

/* start kernel */
void main(void)
{
 	clear_screen();
 	isr_init();
 	irq_init();

 	k_print("HEllo");
 	return;
}

void user_input(s8_int* input)
{
    if (strcmp(input, "END") == 0) {
        k_print("Stopping the CPU. Bye!\n");
        __asm__ __volatile__("hlt");
    }
    k_print("You said: ");
    k_print(input);
    k_print("\n> ");
}