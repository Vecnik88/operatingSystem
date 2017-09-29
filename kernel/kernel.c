#include "../drivers/monitor.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void main() {
	monitor_clear();
	monitor_write("kernel run\n");
	isr_init();

	__asm__ __volatile__("int $2");
	__asm__ __volatile__("int $3");
}