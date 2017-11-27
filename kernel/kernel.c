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
#include <stdint.h>

int start_kernel(uintptr_t mb_info_phys)
{ 	
	hal_init();
	init_timer(50);
	paging_init();

	printk("Hello, paging world!\n");

	uint32_t *ptr = (uint32_t*)0xb0000000;
	uint32_t do_page_fault = *ptr;

	uint32_t *ptr1 = (uint32_t*)0xb0000000;
	uint32_t do_page_fault1 = *ptr1;
}

