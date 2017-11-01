#include <AOS-unix/descriptor_tables.h>
#include <AOS-unix/string.h>
#include <AOS-unix/printk.h>

extern void gdt_flush(uint32_t);
extern void idt_flush(uint32_t);

gdt_segment_t gdt_descriptor[5];
GDTR gdt_ptr;
idt_interrupt_t idt_descriptor[256];
IDTR idt_ptr;

static void gdt_set_segment(int32_t num, uint32_t base, uint32_t limit,
							uint8_t access, uint8_t gran);
static void idt_set_interrupt(uint8_t num, uint32_t base,
							  uint16_t sel, uint8_t flags);

static void gdt_init()
{
	gdt_ptr.limit = sizeof(gdt_segment_t) * 5 - 1;
	gdt_ptr.base = (uint32_t)&gdt_descriptor;

	gdt_set_segment(0, 0x0, 0x0, 0x0, 0x0);
	/* сегмент кода ядра */
	gdt_set_segment(1, 0, 0xffffffff, 0x9a, 0xcf);
	/* сегмент данных ядра */
	gdt_set_segment(2, 0, 0xffffffff, 0x92, 0xcf);
	/* сегмент кода пространства пользователя */
	gdt_set_segment(3, 0, 0xffffffff, 0xfa, 0xcf);
	/* сегмент данных пространства пользователя */
	gdt_set_segment(4, 0, 0xffffffff, 0xfa, 0xcf);

	gdt_flush((uint32_t) &gdt_ptr);

	printk("GDT init\n");
}

static void idt_init()
{
	idt_ptr.limit = sizeof(idt_interrupt_t)*256 - 1;
	idt_ptr.base = (uint32_t)&idt_descriptor;

	memset(&idt_descriptor, '\0', sizeof(idt_interrupt_t) * 256);

	idt_set_interrupt(0, (uint32_t)isr0, 0x08, 0x8e);
	idt_set_interrupt(1, (uint32_t)isr1, 0x08, 0x8e);
	idt_set_interrupt(2, (uint32_t)isr2, 0x08, 0x8e);
	idt_set_interrupt(3, (uint32_t)isr3, 0x08, 0x8e);
	idt_set_interrupt(4, (uint32_t)isr4, 0x08, 0x8e);
	idt_set_interrupt(5, (uint32_t)isr5, 0x08, 0x8e);
	idt_set_interrupt(6, (uint32_t)isr6, 0x08, 0x8e);
	idt_set_interrupt(7, (uint32_t)isr7, 0x08, 0x8e);
	idt_set_interrupt(8, (uint32_t)isr8, 0x08, 0x8e);
	idt_set_interrupt(9, (uint32_t)isr9, 0x08, 0x8e);
	idt_set_interrupt(10, (uint32_t)isr10, 0x08, 0x8e);
	idt_set_interrupt(11, (uint32_t)isr11, 0x08, 0x8e);
	idt_set_interrupt(12, (uint32_t)isr12, 0x08, 0x8e);
	idt_set_interrupt(13, (uint32_t)isr13, 0x08, 0x8e);
	idt_set_interrupt(14, (uint32_t)isr14, 0x08, 0x8e);
	idt_set_interrupt(15, (uint32_t)isr15, 0x08, 0x8e);
	idt_set_interrupt(16, (uint32_t)isr16, 0x08, 0x8e);
	idt_set_interrupt(17, (uint32_t)isr17, 0x08, 0x8e);
	idt_set_interrupt(18, (uint32_t)isr18, 0x08, 0x8e);
	idt_set_interrupt(19, (uint32_t)isr19, 0x08, 0x8e);
	idt_set_interrupt(20, (uint32_t)isr20, 0x08, 0x8e);
	idt_set_interrupt(21, (uint32_t)isr21, 0x08, 0x8e);
	idt_set_interrupt(22, (uint32_t)isr22, 0x08, 0x8e);
	idt_set_interrupt(23, (uint32_t)isr23, 0x08, 0x8e);
	idt_set_interrupt(24, (uint32_t)isr24, 0x08, 0x8e);
	idt_set_interrupt(25, (uint32_t)isr25, 0x08, 0x8e);
	idt_set_interrupt(26, (uint32_t)isr26, 0x08, 0x8e);
	idt_set_interrupt(27, (uint32_t)isr27, 0x08, 0x8e);
	idt_set_interrupt(28, (uint32_t)isr28, 0x08, 0x8e);
	idt_set_interrupt(29, (uint32_t)isr29, 0x08, 0x8e);
	idt_set_interrupt(30, (uint32_t)isr30, 0x08, 0x8e);
	idt_set_interrupt(31, (uint32_t)isr31, 0x08, 0x8e);

	idt_flush((uint32_t)&idt_ptr);

	printk("IDT init\n");
}

static void gdt_set_segment(int32_t num, uint32_t base, uint32_t limit,
							uint8_t access, uint8_t gran)
{
   gdt_descriptor[num].base_low    = (base & 0xFFFF);
   gdt_descriptor[num].base_middle = (base >> 16) & 0xFF;
   gdt_descriptor[num].base_high   = (base >> 24) & 0xFF;

   gdt_descriptor[num].limit_low   = (limit & 0xFFFF);
   gdt_descriptor[num].granularity = (limit >> 16) & 0x0F;

   gdt_descriptor[num].granularity |= gran & 0xF0;
   gdt_descriptor[num].access      = access;
}

static void idt_set_interrupt(uint8_t num, uint32_t base,
							  uint16_t sel, uint8_t flags)
{
	idt_descriptor[num].base_low = base & 0xffff;
	idt_descriptor[num].base_high = (base >> 16) & 0xffff;
	idt_descriptor[num].sel = sel;
	idt_descriptor[num].always0 = 0;
	/* раскомментировать для пользовательского режима */
	idt_descriptor[num].flags = flags /* | 0x60 */;
}
void gdt_idt_init()
{
	gdt_init();
	idt_init();
}