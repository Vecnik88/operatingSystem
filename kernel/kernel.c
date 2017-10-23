#include "multiboot.h"
#include "vga.h"

int start_kernel(struct multiboot* multiboot)
{
	monitor_init();
	monitor_clear();
	//monitor_put_char('a');
	monitor_write("Your kernel run bro\n");
	monitor_write("Your kernel run bro\n");
	printf("Hello %d\n", 5);
}