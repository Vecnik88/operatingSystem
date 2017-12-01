#include <AOS-unix/hal.h>
#include <AOS-unix/descriptor_tables.h>
#include <AOS-unix/printk.h>
#include <AOS-unix/vga.h>

void hal_init()
{
	gdt_idt_init();
	printk("Hal initialize\n");
}

void hal_shutdown()
{

}