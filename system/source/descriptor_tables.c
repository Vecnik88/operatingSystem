#include "../../drivers/common.h"
#include "../include/descriptor_tables.h"

/* предоставляет доступ к ассемблерной функции */
extern void gdt_flush(u32_int);

static void init_gdt();
static void gdt_set_gate(s32_int, u32_int, u32_int, u8_int, u8_int);

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

void init_descriptor_tables()
{
	init_gdt();
}

static void init_gdt()
{
	gdt_ptr.limit = (sizeof(gdt_entry_t)*5) - 1;
	gdt_ptr.base = (u32_int)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);					// нулевой сегмент
	gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf);		// сегмент кода
	gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf);
	gdt_set_gate(3, 0, 0xffffffff, 0xfa, 0xcf);
	gdt_set_gate(4, 0, 0xffffffff, 0xf2, 0xcf);

	gdt_flush((u32_int)&gdt_ptr);
}

static void gdt_set_gate(s32_int num, u32_int base, u32_int limit, u8_int access, u8_int gran)
{
	gdt_entries[num].base_low = (base & 0xffff);
	gdt_entries[num].base_middle = (base >> 16) & 0xff;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;
	gdt_entries[num].limit_low = (limit & 0xffff);
	gdt_entries[num].granularity = (limit >> 16) & 0x0f;
	gdt_entries[num].granularity |= gran & oxf0;
	gdt_entries[num].access = access;
}