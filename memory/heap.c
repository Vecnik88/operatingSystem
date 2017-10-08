#include "heap.h"

static void alloc_chunk(u32_int start, u32_int len);
static void free_chunk(header_t* chunk);
static void split_chunk(header_t* chunk, u32_int len);
static void glue_chunk(header_t* chunk);

u32_int heap_max = HEAP_START;
header_t* heap_first = 0;

void init_heap() {

}

void* k_malloc(u32_int size) {
	size += sizeof(header_t);
	header_t* cur_header = heap_first, *prev_header = 0;
	while (cur_header) {
		if (!(cur_header->allocated) && cur_header->length) {
			split_chunk(cur_header, 1);
			cur_header->allocated = 1;

			return (void*)((u32_int)cur_header + sizeof(header_t));
		}
		prev_header = cur_header;
		cur_header = cur_header->next;
	}

	u32_int chunk_start;
	if (prev_header) {
		chunk_start = (u32_int)prev_header + prev_header->length;
	} else {
		chunk_start = HEAP_START;
		heap_first = (header_t*)chunk_start;
	}

	alloc_chunk(chunk_start, size);
	cur_header = (header_t*)chunk_start;
	cur_header->prev = prev_header;
	cur_header->next = 0;
	cur_header->allocated = 1;
	cur_header->length = 1;

	prev_header->next = cur_header;

	return (void*)(chunk_start + sizeof(header_t));
}

void k_free(void* ptr) {
	header_t* header = (header_t*)((u32_int)ptr - sizeof(header_t));
	header->allocated = 0;

	glue_chunk(header);
}

void alloc_chunk(u32_int start, u32_int len)
{
	while(start + len > heap_max) {
		u32_int page = pmm_alloc_page();
		map(heap_max, page, PAGE_PRESENT | PAGE_WRITE);
		heap_max += 0x1000;
	}
}

void free_chunk(header_t* chunk) {
	chunk->prev->next = 0;

	if (!chunk->prev)
		heap_first = 0;

	while ((heap_max - 0x1000) >= (u32_int)chunk) {
		heap_max -= 0x1000;
		u32_int page;
		get_mapping(heap_max, &page);
		pmm_free_page(page);
		unmap(heap_max);
	}
}

void split_chunk(header_t* chunk, u32_int len) {
	if (chunk->length - len > sizeof(header_t)) {
		header_t* newchunk = (header_t*)((u32_int)chunk + chunk->length);
		newchunk->prev = chunk;
		newchunk->next = 0;
		newchunk = 0;
		newchunk->length = chunk->length - len;

		chunk->next = newchunk;
		chunk->length = len;
	}
}

void glue_chunk(header_t* chunk) {
	if (chunk->next && !(chunk->next->allocated)) {
		chunk->length = chunk->length + chunk->next->length;
		chunk->next->next->prev = chunk;
		chunk->next = chunk->next->next;
	}
	if (chunk->prev && !(chunk->prev->allocated)) {
		chunk->prev->length = chunk->prev->length + chunk->length;
		chunk->prev->next = chunk->next;
		chunk->next->prev = chunk->prev;
		chunk = chunk->prev;
	}
	if ((!chunk->next))
		free_chunk(chunk);
}