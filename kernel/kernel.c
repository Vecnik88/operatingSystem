#include <AOS-unix/multiboot.h>
#include <AOS-unix/vga.h>
#include <AOS-unix/printk.h>
#include <AOS-unix/descriptor_tables.h>
#include <AOS-unix/vga_graph.h>

int start_kernel(struct multiboot* multiboot)
{
	void gdt_idt_init();
	monitor_init();
	monitor_clear();
	printk("gdt_init\n");
	//monitor_put_char('a');
	monitor_write("Your kernel run bro\n");
	monitor_write("Your kernel run bro\n");
	//vbe_set(1200, 1200, 1200);
	//vbe_set(200, 200, 200);
	printk("Hello 0x%lu-0x%lu", 52320390239, 42342);

	//VGA_init();
	//monitor_clear();
	printk("Hello 0x%lu-0x%lu", 52320390239, 42342);
	//monitor_write("Your kernel run bro\n");
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
}

