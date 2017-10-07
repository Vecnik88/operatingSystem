#include "vmm.h"
#include "pmm.h"
#include "idt.h"

u32_int* page_directory = (u32_int*)PAGE_DIR_VIRTUAL_ADDR;
u32_int* page_tables = (u32_int*)PAGE_TABLE_VIRTUAL_ADDR;

page_directory_t* current_directory;

extern char pmm_paging_active;

void page_fault(registers_t* regs);

void init_vmm()
{
	u32_int i;
	u32_int cr0;

	register_interrupt_handler(14, &page_fault);

	page_directory_t* pd = (page_directory_t)pmm_alloc_page();

	mem_set(pd, 0, 0x1000);

	pd[0] = pmm_alloc_page() | PAGE_PRESENT | PAGE_WRITE;
	u32_int* pt = (u32_int*)(pd[0] & PAGE_MASK);

	for (i = 0; i < 1024; ++i)
		pt[i] = i*0x1000 | PAGE_PRESENT | PAGE_WRITE;

	pd[1022] = pmm_alloc_page() | PAGE_PRESENT | PAGE_WRITE;
	pt = (u32_int*)(pd[1022] & PAGE_MASK);
	mem_set(pt, 0, 0x1000);

	pt[1023] = (u32_int)pd | PAGE_PRESENT | PAGE_WRITE;

	switch_page_directory(pd);

	__asm__ __volatile__("mov %%cr0, %0" : "=r" (cr0));
	cr0 |= 0x80000000;
	__asm__ __volatile__("mov %0, %%cr0" : : "r" (cr0));

	u32_int pt_idx = PAGE_DIR_IDX((PMM_STACK_ADDR >> 12));
	page_directory[pt_idx] = pmm_alloc_page() | PAGE_PRESENT | PAGE_WRITE;
	mem_set(page_tables[pt_idx*1024], 0, 0x1000);

	pmm_paging_active = 1;
}