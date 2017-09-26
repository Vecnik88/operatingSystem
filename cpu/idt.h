#ifndef IDT_H
#define IDT_H

#include "types.h"

/* селектор сегмента */
#define KERNEL_CS 0x08

typedef struct {
	u16_int low_offset;
	u16_int sel;
	u8_int always0;		/* всегда 0 */
	u8_int flags;
	u16_int high_offset;
} __attribute__((packed)) idt_gate_t;

typedef struct {
	u16_int limit;
	u32_int base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

void set_idt_gate(int n, u32_int handler);
void set_idt();

#endif