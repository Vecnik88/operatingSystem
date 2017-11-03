#include <AOS-unix/multiboot.h>
#include <AOS-unix/vga.h>
#include <AOS-unix/printk.h>
#include <AOS-unix/descriptor_tables.h>
#include <AOS-unix/vga_graph.h>
#include <AOS-unix/timer.h>
#include <AOS-unix/keyboard.h>

int start_kernel(struct multiboot* multiboot)
{ 
	
	monitor_init();
	monitor_clear();
	gdt_idt_init();
	init_keyboard();
	//printk("gdt_init\n");
	//monitor_put_char('a');
	//monitor_write("Your kernel run bro\n");
	//monitor_write("Your kernel run bro\n");
	//vbe_set(1200, 1200, 1200);
	//vbe_set(200, 200, 200);
	//printk("Hello 0x%lu-0x%lu", 52320390239, 42342);

	//VGA_init();
	//monitor_clear();
	//printk("Hello 0x%lu-0x%lu", 52320390239, 42342);
	//monitor_write("Your kernel run bro\n");
	//asm volatile("sti");
	init_timer(50);
	//printk("timer init");
	//asm volatile ("int $0x3");
	//asm volatile ("int $0x4");
}

