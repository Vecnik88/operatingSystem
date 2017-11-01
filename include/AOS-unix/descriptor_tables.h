#ifndef DESCRIPTOR_TABLE_H
#define DESCRIPTOR_TABLE_H

#include <stdarg.h>
#include <stdint.h>

void gdt_idt_init();

/**
	1 дескриптор в gdt занимает 64 бита
	и описывает 1 сегмент
 **/
struct gdt_segment_descriptor {
	/* младшие 16 битов граничного значения лимит */
	uint16_t limit_low;
	/* младшие 16 бит адреса начала сегмента */
	uint16_t base_low;
	/* следующие 8 бит адреса начала сегмента */
	uint8_t base_middle;
	/**
		флаги доступа, определяющие 
		в каком кольце можно использовать сегмент
	 **/
	uint8_t access;
	uint8_t granularity;
	/* последние 8 бит адреса */
	uint8_t base_high;
}__attribute__((packed));
/**
	__attribute__((packed)) - означает, что поля в 
	структуру упаковываются без дырок
 **/
typedef struct gdt_segment_descriptor gdt_segment_t;

struct gdt_ptr {
	/* размер таблицы gdt */
	uint16_t limit;
	/* адрес таблицы gdt в памяти */
	uint32_t base;
}__attribute__((packed));
typedef struct gdt_ptr GDTR;

struct idt_interrupt {
	/* младшие 16 бит куда происходит прерывание */
	uint16_t base_low;
	/* переключатель ядра */
	uint16_t sel;
	/* всегда ноль */
	uint8_t always0;
	/* флаги */
	uint8_t flags;
	/* старшие 16 бит, куда происходит прерывание */
	uint16_t base_high;
}__attribute__((packed));
typedef struct idt_interrupt idt_interrupt_t;

struct idt_ptr {
	/* размер таблицы idt */
	uint16_t limit;
	/* адрес таблицы idt в памяти */
	uint32_t base;
}__attribute__((packed));
typedef struct idt_ptr IDTR;

extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif	/* DESCRIPTOR_TABLE_H */