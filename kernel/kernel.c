#include "../drivers/include/monitor.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

int main() {
	isr_init();

	__asm__ __volatile__("int $2");
	__asm__ __volatile__("int $3");
}