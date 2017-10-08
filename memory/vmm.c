#include "vmm.h"

u32_int* page_directory = (u32_int*)PAGE_DIR_VIRTUAL_ADDR;
u32_int* page_tables = (u32_int*)PAGE_TABLE_VIRTUAL_ADDR;

page_directory_t* current_directory;

extern s8_int pmm_paging_active;

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
	cr0 |= 0x40000000;
	__asm__ __volatile__("mov %0, %%cr0" : : "r" (cr0));

	u32_int pt_idx = PAGE_DIR_IDX((PMM_STACK_ADDR >> 12));
	page_directory[pt_idx] = pmm_alloc_page() | PAGE_PRESENT | PAGE_WRITE;
	mem_set(page_tables[pt_idx*1024], 0, 0x1000);

	pmm_paging_active = 1;
}

void switch_page_directory(page_directory_t* pd)
{
	current_directory = pd;
	__asm__ __volatile__("mov %0, %%cr3" : : "r"(pd));
}

void map(u32_int va, u32_int pa, u32_int flags)
{
	u32_int virual_page = va/0x1000;
	u32_int pt_idx = PAGE_DIR_IDX(virual_page);

	if (!page_directory[pt_idx]) {
		page_directory[pt_idx] = pmm_alloc_page() | PAGE_PRESENT | PAGE_WRITE;
		mem_set(page_tables[pt_idx*1024], 0, 0x1000);
	}

	page_tables[virual_page] = (pa & PAGE_MASK) | flags;
}

void unmap(u32_int va)
{
	u32_int virtual_page = va/0x1000;
	page_tables[virtual_page] = 0;

	__asm__ __volatile__ ("invlpg (%0)" : : "a" (va));
}

s8_int get_mapping(u32_int va, u32_int* pa)
{
	u32_int virtual_page = va/0x1000;
	u32_int pt_idx = PAGE_DIR_IDX(virtual_page);

	if (!page_directory[pt_idx])
		return 0;

	if (page_tables[virtual_page] != 0) {
		if(pa) 
			*pa = page_tables[virtual_page] & PAGE_MASK;

		return 1;
	}
}

void page_fault(registers_t* regs)
{
	u32_int cr2;
	__asm__ __volatile__("mov %%cr2, %0" : "=r" (cr2));
	k_print("Page fault\n");

  	while(1) {

  	}
}