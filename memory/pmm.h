#ifndef PMM_H
#define PMM_H

#include "../cpu/types.h"
#include "vmm.h"

#define PMM_STACK_ADDR 0xff000000

void init_pmm(u32_int start);

u32_int pmm_alloc_page();

void pmm_free_page(u32_int ptr);

#endif