#include "pmm.h"

u32_int pmm_stack_loc = PMM_STACK_ADDR;
u32_int pmm_stack_max = PMM_STACK_ADDR;
u32_int pmm_location;
s8_int pmm_paging_active = 0;

void init_pmm(u32_int start)
{
	pmm_location = (start + 0x1000) & PAGE_MASK;
}

u32_int pmm_alloc_page()
{
	if (pmm_paging_active) {
		if (pmm_stack_loc == PMM_STACK_ADDR)
			k_print("Error: out of memory\n");

		pmm_stack_loc -= sizeof(u32_int);
		u32_int* stack = (u32_int*)pmm_stack_loc;

		return *stack;
	} else {
		return pmm_location += 0x1000;
	}
}

void pmm_free_page(u32_int ptr)
{
	if (ptr < pmm_location)
		return;

	if (pmm_stack_max <= pmm_stack_loc) {
		map(pmm_stack_max, ptr, PAGE_PRESENT | PAGE_WRITE);
		pmm_stack_max += 4096;
	} else {
		u32_int* stack = (u32_int*)pmm_stack_loc;
		*stack = ptr;
		pmm_stack_loc += sizeof(u32_int);
	}
}