#include "../drivers/monitor.h"

/* start function in my kernel */
void main() {
	clear_monitor();
	k_print("Hello Anton\n");
}