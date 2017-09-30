#include "../drivers/monitor.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

/* start function in my kernel */
void main() {
	clear_monitor();
	k_print("Hello Anton\n");

	//isr_init();
	//__asm__ __volatile__ ("int $2");
	//__asm__ __volatile__ ("int $3");
}