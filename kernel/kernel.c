//#include "../drivers/monitor.h"
//#include "../cpu/isr.h"
//#include "../cpu/idt.h"
#include "../drivers/ports.h"

void main() {
	clear_monitor();
	k_print("Hello Anton\n");
}