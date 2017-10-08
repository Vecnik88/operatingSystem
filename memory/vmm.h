#ifndef VMM_H
#define VMM_H

#include "../cpu/types.h"
#include "../cpu/isr.h"
#include "pmm.h"
#include "../cpu/idt.h"

#define PAGE_DIR_VIRTUAL_ADDR	0xffbff000
#define PAGE_TABLE_VIRTUAL_ADDR	0xffc00000
#define PAGE_DIR_IDX(x) ((u32_int)x/1024)
#define PAGE_TABLE_IDX(x) ((u32_int)x%1024)

#define PAGE_PRESENT 	0x1
#define PAGE_WRITE 		0x2
#define PAGE_USER		0x4
#define PAGE_MASK		0xfffff000

typedef u32_int page_directory_t;

void init_vmm();
void switch_page_directory(page_directory_t* pd);
void map(u32_int va, u32_int pa, u32_int flags);
void unmap(u32_int va);
s8_int get_mapping(u32_int va, u32_int* pa);

#endif