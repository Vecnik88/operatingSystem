#ifndef DESCRIPTOR_TABLE_H
#define DESCRIPTOR_TABLE_H

#include <stdarg.h>
#include <stdint.h>
#include <AOS-unix/string.h>

struct gdt_desc {
	uint16_t limit_low;		/* младшие 16 битов значения limit */
	uint16_t base_low;		/* младшие 16 битов адресной базы */
	uint8_t base_middle;	/* следующие 8 битов адресной базы */
/**
	формат байта доступа:
		7б 		- присутствие сегмента(1 - да);
		4б - 6б	- кольцо 0-3;
		3б		- тип дескриптора;
		0б - 2б	- тип сегмента(код, данные);
 **/
	uint8_t access;			
/**
	формат байта гранулярности:
		7б 		- гранулярность(0 = 1 байт, 1 = 1 кбайт);
		6б		- размер операнда(0 = 16 бит, 1 = 32 бита);
		5б		- всегда 0;
		4б		- возможность доступа из системы(всегда 0);
		0б - 2б	- длина сегмента;
 **/
	uint8_t granularity;
	uint8_t base_high;		/* последние 8 бит адресной базы */
} __attribute__((packed));

typedef struct gdt_desc gdt_desc_t;

struct gdt_ptr {
	uint16_t limit;		/* размер таблицы gdt */
	uint32_t base;		/* адрес первого дескриптора(нулевого) */
} __attribute__ ((packed));
typedef struct gdt_ptr gdt_ptr_t;

struct idt_desk {
	uint16_t base_lo;	/* младшие 16 битов куда происходит переход */
	uint16_t sel;		/* переключатль сегмента ядра */
	uint8_t always0;	/* всегда 0 */
	uint8_t flags;		/* флаги */
	uint16_t base_hi;	/* старшие 16 битов адресов куда происходит переход */
} __attribute__ ((packed));
typedef struct idt_desk idt_desc_t;

struct idt_ptr {
	uint16_t limit;		/* размер таблицы idt */
	uint32_t base;		/* адрес первого элемента массива idt */
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

void gdt_idt_init();

/* наши обработчики прерываний, написанные на ассемблере */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
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

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif	/* DESCRIPTOR_TABLE_H */