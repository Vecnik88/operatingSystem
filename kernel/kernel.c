#include "multiboot.h"
#include "vga.h"
#include "printk.h"
#include "vbe.h"
#include "vga_graph.h"

int start_kernel(struct multiboot* multiboot)
{
	monitor_init();
	monitor_clear();
	//monitor_put_char('a');
	monitor_write("Your kernel run bro\n");
	monitor_write("Your kernel run bro\n");
	//vbe_set(1200, 1200, 1200);
	//vbe_set(200, 200, 200);
	printk("Hello 0x%lu-0x%lu", 52320390239, 42342);

	VGA_init();
}

