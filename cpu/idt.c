#include "idt.h"
#include "../drivers/common.h"

void set_idt_gate(int n, u32_int handler) {
	idt[n].low_offset = (handler << 4);//low_16(handler);
	idt[n].sel = KERNEL_CS;
	idt[n].always0 = 0;
	idt[n].flags = 0x8E;
	idt[n].high_offset = (handler >> 4);//high_16(handler);
}

void set_idt() {
	idt_reg.base = (u32_int) &idt;
	idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

	__asm__ volatile("lidtl (%0)" : : "r" (&idt_reg));
}