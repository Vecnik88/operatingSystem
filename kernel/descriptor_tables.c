#include <AOS-unix/descriptor_tables.h>
#include <AOS-unix/port.h>

extern void gdt_flush(uint32_t addr_gdt);
extern void idt_flush(uint32_t addr_idt);

static void init_gdt();
static void init_idt();

static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_desc_t	gdt_entries[5];
gdt_ptr_t	gdt_ptr;
idt_desc_t	idt_entries[256];
idt_ptr_t	idt_ptr;

void gdt_idt_init()
{
	init_gdt();
	init_idt();
}

static void init_idt()
{
	idt_ptr.limit = sizeof(idt_desc_t) * 256 - 1;
	idt_ptr.base = (uint32_t)&idt_entries;

	memset(&idt_entries, 0, sizeof(idt_entries) * 256);

	idt_set_gate(0, (uint32_t) isr0, 0x08, 0x8e);
	idt_set_gate(1, (uint32_t) isr1, 0x08, 0x8e);
	idt_set_gate(2, (uint32_t) isr2, 0x08, 0x8e);
	idt_set_gate(3, (uint32_t) isr3, 0x08, 0x8e);
	idt_set_gate(4, (uint32_t) isr4, 0x08, 0x8e);
	idt_set_gate(5, (uint32_t) isr5, 0x08, 0x8e);
	idt_set_gate(6, (uint32_t) isr6, 0x08, 0x8e);
	idt_set_gate(7, (uint32_t) isr7, 0x08, 0x8e);
	idt_set_gate(8, (uint32_t) isr8, 0x08, 0x8e);
	idt_set_gate(9, (uint32_t) isr9, 0x08, 0x8e);
	idt_set_gate(10, (uint32_t) isr10, 0x08, 0x8e);
	idt_set_gate(11, (uint32_t) isr11, 0x08, 0x8e);
	idt_set_gate(12, (uint32_t) isr12, 0x08, 0x8e);
	idt_set_gate(13, (uint32_t) isr13, 0x08, 0x8e);
	idt_set_gate(14, (uint32_t) isr14, 0x08, 0x8e);
	idt_set_gate(15, (uint32_t) isr15, 0x08, 0x8e);
	idt_set_gate(16, (uint32_t) isr16, 0x08, 0x8e);
	idt_set_gate(17, (uint32_t) isr17, 0x08, 0x8e);
	idt_set_gate(18, (uint32_t) isr18, 0x08, 0x8e);
	idt_set_gate(19, (uint32_t) isr19, 0x08, 0x8e);
	idt_set_gate(20, (uint32_t) isr20, 0x08, 0x8e);
	idt_set_gate(21, (uint32_t) isr21, 0x08, 0x8e);
	idt_set_gate(22, (uint32_t) isr22, 0x08, 0x8e);
	idt_set_gate(23, (uint32_t) isr23, 0x08, 0x8e);
	idt_set_gate(24, (uint32_t) isr24, 0x08, 0x8e);
	idt_set_gate(25, (uint32_t) isr25, 0x08, 0x8e);
	idt_set_gate(26, (uint32_t) isr26, 0x08, 0x8e);
	idt_set_gate(27, (uint32_t) isr27, 0x08, 0x8e);

	idt_flush((uint32_t)&idt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
	idt_entries[num].base_lo = base & 0xffff;
	idt_entries[num].base_hi = (base >> 16) & 0xffff;

	idt_entries[num].sel = sel;
	idt_entries[num].always0 = 0x0;

	/* расскоментировать для пользовательского режима(3) */
	idt_entries[num].flags = flags /* | 0x60 */
}

static void init_gdt()
{
	gdt_ptr.limit = sizeof(gdt_desc_t) * 5 - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;

	/* устанавливаем сегменты */

	/* нулевой дескриптор */
	gdt_set_gate(0, 0, 0, 0, 0);
	/* сегмент кода ядра */
	gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf);
	/* сегмент данных ядра */
	gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf);
	/* сегмент кода пользовательского пространства */
	gdt_set_gate(3, 0, 0xffffffff, 0xfa, 0xcf);
	/* сегмент данных пользовательского пространства */
	gdt_set_gate(4, 0, 0xffffffff, 0xf2, 0xcf);

	/* загружаем таблицу gdt в регист GDTT */
	gdt_flush((uint32_t)&gdt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit,
						 uint8_t access, uint8_t gran) 
{
	gdt_entries[num].base_low = (base & 0xffff);
	gdt_entries[num].base_middle = (base >> 16) & 0xff;
	gdt_entries[num].base_high = (base >> 24) & 0xff;

	gdt_entries[num].limit_low = (limit & 0xffff);
	gdt_entries[num].granularity = (limit >> 16) & 0x0f;

	gdt_entries[num].granularity |= gran & 0xf0;
	gdt_entries[num].access = access;
}