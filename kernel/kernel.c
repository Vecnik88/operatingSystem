#include <AOS-unix/multiboot.h>
#include <AOS-unix/vga.h>
#include <AOS-unix/printk.h>
#include <AOS-unix/descriptor_tables.h>
#include <AOS-unix/vga_graph.h>
#include <AOS-unix/timer.h>
#include <AOS-unix/keyboard.h>
#include <AOS-unix/cpuid.h>
#include <AOS-unix/paging.h>
#include <stdint.h>

int start_kernel(uintptr_t mb_info_phys)
{ 	
	//const struct multiboot_info * const info = va(mb_info_phys);
	monitor_init();
	monitor_clear();
	gdt_idt_init();
	//init_keyboard();
	asm volatile("sti");
	init_paging();
	//printk("gdt_init\n");
	//monitor_put_char('a');
	//monitor_write("Your kernel run bro\n");
	//monitor_write("Your kernel run bro\n");
	//vbe_set(1200, 1200, 1200);
	//vbe_set(200, 200, 200);
    /* Test the interrupts */
    //__asm__ __volatile__("int $2");
    //__asm__ __volatile__("int $3");
	//init_timer(50);
	//VGA_init();
	//monitor_clear();
	printk("Hello 0x%lu-0x%lu", 52320390239, 42342);
	//monitor_write("Your kernel run bro");
	//init_timer(50);
	//asm volatile("sti");
	//print_info_cpu();
	//printk("timer init");
	//asm volatile ("int $0x3");
	//asm volatile ("int $0x13");
//	asm volatile ("int $0x12");
//	asm volatile ("int $0x13");
}

