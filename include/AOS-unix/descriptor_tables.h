#ifndef DESCRIPTOR_TABLE_H
#define DESCRIPTOR_TABLE_H

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

typedef struct gdt_desc gdt_desc;

struct gdt_ptr {
	uint16_t limit;		/* верхние 16 битов всех предельных значений селектора */
	uint32_t base;		/* адрес первого дескриптора(нулевого) */
} __attribute__ ((packed));

void gdt_idt_init();

#endif	/* DESCRIPTOR_TABLE_H */