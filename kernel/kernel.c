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
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>

/* Higher 2 GB of 64 bit logical address space start from this address */
#define VIRTUAL_BASE	0xffffffff80000000

/* First address after "canonical hole", beginning of the middle mapping. */
#define HIGHER_BASE	0xffff800000000000

#define VA(x) ((void *)((uintptr_t)x + HIGHER_BASE))
#define PA(x) ((uintptr_t)x - HIGHER_BASE);

static inline void *va(uintptr_t phys)
{ return VA(phys); }

static inline uintptr_t pa(const void *virt)
{ return PA(virt); }

static void print_memmap(const struct multiboot_info *info)
{
	if ((info->flags & MULTIBOOT_INFO_MEM_MAP) == 0) {
		printk("No memory map provided\n");
		return;
	}

	const uintptr_t begin = info->mmap_addr;
	const uintptr_t end = begin + info->mmap_length;
	uintptr_t ptr = begin;

	printk("Memory Map:\n");
	while (ptr + sizeof(struct multiboot_mmap_entry) <= end) {
		const struct multiboot_mmap_entry *e = va(ptr);
		const unsigned long long from = e->addr;
		const unsigned long long to = from + e->len;

		printk("range [0x%llx-0x%llx) %s\n", from, to,
				e->type == MULTIBOOT_MEMORY_AVAILABLE
				? "available" : "reserved");
		ptr += e->size + sizeof(e->size);
	}
}

int start_kernel(uintptr_t mb_info_phys)
{ 	
	hal_init();
	init_timer(50);
	paging_init();

	printk("Hello, paging world!\n");

	const struct multiboot_info * const info = va(mb_info_phys);
	print_memmap(info);
	//uint32_t *ptr = (uint32_t*)0xb0000000;
	//uint32_t do_page_fault = *ptr;

	//uint32_t *ptr1 = (uint32_t*)0xb0000000;
	//uint32_t do_page_fault1 = *ptr1;
}

