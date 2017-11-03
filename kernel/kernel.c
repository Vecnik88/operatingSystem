#include <AOS-unix/multiboot.h>
#include <AOS-unix/vga.h>
#include <AOS-unix/printk.h>
<<<<<<< HEAD
//#include <AOS-unix/vga_graph.h>
#include <AOS-unix/timer.h>
#include <AOS-unix/idt.h>
#include <AOS-unix/isr.h>
=======
#include <AOS-unix/descriptor_tables.h>
#include <AOS-unix/vga_graph.h>
#include <AOS-unix/timer.h>
>>>>>>> parent of dc68c92... gdt idt refresh

int start_kernel(struct multiboot* multiboot)
{ 
<<<<<<< HEAD
	//monitor_init();
	/*const struct multiboot_info * const info = mb_info_phys;	
	monitor_init();
	monitor_clear();
	monitor_write_dec(info->mmap_length);
	printk("hello user %lu=%lu\n", info->mmap_length, info->mmap_addr);
	printk("\n12");*/
	//gdt_idt_init();
=======
	
	monitor_init();
	monitor_clear();
	gdt_idt_init();
>>>>>>> parent of dc68c92... gdt idt refresh
	//printk("gdt_init\n");
	//monitor_put_char('a');
	//monitor_write("Your kernel run bro\n");
	//monitor_write("Your kernel run bro\n");
	//vbe_set(1200, 1200, 1200);
	//vbe_set(200, 200, 200);
	//printk("Hello 0x%lu-0x%lu", 52320390239, 42342);
	isr_install();
    /* Test the interrupts */
    //__asm__ __volatile__("int $2");
    //__asm__ __volatile__("int $3");
	//init_timer(50);
	//VGA_init();
	//monitor_clear();
	//printk("Hello 0x%lu-0x%lu", 52320390239, 42342);
	//monitor_write("Your kernel run bro\n");
<<<<<<< HEAD
	init_timer(50);
	asm volatile("sti");
	//printk("timer init");
	//asm volatile ("int $0x3");
	//asm volatile ("int $0x13");
//	asm volatile ("int $0x12");
//	asm volatile ("int $0x13");
=======
	init_timer(100);
	//printk("timer init");
	//asm volatile ("int $0x3");
	//asm volatile ("int $0x4");
>>>>>>> parent of dc68c92... gdt idt refresh
}

