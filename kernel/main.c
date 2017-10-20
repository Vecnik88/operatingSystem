#include "screen.h"
#include "descriptor_tables.h"

void start_kernel(struct multiboot *mboot_ptr)
{
	init_descriptor_tables();

	screen_clear();
	screen_write("Hello world\n");

	asm volatile("int $0x3");
    asm volatile("int $0x4");
}