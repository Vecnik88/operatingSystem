#include "bootmem.h"

void bootmem_init(u32_int start)
{
	init_pmm(start);
	k_print("Physical memory init\n");
	init_vmm();
	k_print("Virtual memory init\n");
	init_heap();
	k_print("Heap init\n");
}