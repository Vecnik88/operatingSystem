#ifndef IDT_H
#define IDT_H

#include "types.h"

#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

typedef struct {
	u16_int low_offset;					/* младшие 16 бит адреса функции обработчика */
	u16_int sel;						/* селектор ядра */
	u8_int always0;						/* всегда 0 */
	/* флаги:
	 * 7 бит "если установлен, прерывание присутствует"
	 * 5-6 бит "уровень привилегий(0=максимальный, 3=минимальный)"
	 * 4 бит "0 для прерываний"
	 * 0-3 бит "1110 - 32 битное прерывание"
	 */
	u8_int flags;
	u16_int high_offset;				/* старшие 16 бит адреса функции обработчика */
} __attribute__((packed)) idt_gate_t;

/* указатель на массив обработчиков прерываний */
typedef struct {
	u16_int limit;
	u32_int base;
} __attribute__((packed)) idt_register_t;

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(s32_int n, u32_int handler);
void set_idt();

#endif