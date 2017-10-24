#include "multiboot.h"
#include "vga.h"
#include "print_k.h"

int start_kernel(struct multiboot* multiboot)
{
	monitor_init();
	monitor_clear();
	//monitor_put_char('a');
	monitor_write("Your kernel run bro\n");
	monitor_write("Your kernel run bro\n");
	printk("Hello 0x%lu-0x%lu", 52320390239, 42342);
}