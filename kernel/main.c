#include "screen.h"
#include "descriptor_tables.h"
#include "paging.h"
#include "timer.h"

void start_kernel(struct multiboot *mboot_ptr)
{
	init_descriptor_tables();
	screen_clear();
	screen_write("Hello, paging world!\n");
	paging_init();	

   u32_int *ptr = (u32_int*)0xA0000000;
   u32_int do_page_fault = *ptr;
}