#ifndef HEAP_H
#define HEAP_H

#include "types.h"

#define HEAP_START 	0xd0000000
#define HEAP_END 	0xffbff000

typedef struct header {
	struct header* prev, *next;
	u32_int allocated : 1;
	u32_int length : 31;
} header_t;

void init_heap();
void* k_malloc(u32_int size);
void k_free(void* ptr);

#endif