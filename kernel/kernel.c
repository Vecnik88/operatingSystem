#include <AOS-unix/multiboot.h>
#include <AOS-unix/vga.h>
#include <AOS-unix/printk.h>
#include <AOS-unix/descriptor_tables.h>
#include <AOS-unix/vga_graph.h>
#include <AOS-unix/timer.h>
#include <AOS-unix/keyboard.h>
#include <AOS-unix/cpuid.h>
#include <AOS-unix/paging.h>
#include <AOS-unix/hal.h>
#include <AOS-unix/keyboard.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>

int start_kernel(uintptr_t mb_info_phys)
{ 	
	hal_init();
	//init_timer(50);
	init_keyboard();
	//paging_init();
}

