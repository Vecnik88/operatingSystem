#ifndef PAGING_H
#define PAGING_H

#include "isr.h"
#include "types.h"

#define PANIC(x) k_print(x); while(1)

typedef struct page {
	u32_int present		: 1;
	u32_int rw			: 1;
	u32_int user		: 1;
	u32_int accessed	: 1;
	u32_int dirty		: 1;
	u32_int unused		: 7;
	u32_int frame		: 20;
} page_t;

typedef struct page_table {
	pa pages[1024];
} page_table_t;

typedef struct page_directory {
	/* маccив указателей на таблицы страниц */
	page_table_t* tables[1024];
	u32_int tablesPhysical[1024];
	u32_int physical_addr;
} page_directory_t;

/* включение страничной организации памяти */
void init_paging();
/* загружает указатель директорий страниц в регистр CR3 */
void switch_page_directory(switch_page_directory* new);
/* поиск указателя на необходимую страницу */
page_t* get_page(u32_int address, int make, page_directory_t* dir);
/* page fault */
void page_fault(registers_t regs);

#endif