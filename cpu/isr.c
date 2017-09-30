#include "isr.h"

void isr_install() 
{
    set_idt_gate(0, (u32_int)isr0);
    set_idt_gate(1, (u32_int)isr1);
    set_idt_gate(2, (u32_int)isr2);
    set_idt_gate(3, (u32_int)isr3);
    set_idt_gate(4, (u32_int)isr4);
    set_idt_gate(5, (u32_int)isr5);
    set_idt_gate(6, (u32_int)isr6);
    set_idt_gate(7, (u32_int)isr7);
    set_idt_gate(8, (u32_int)isr8);
    set_idt_gate(9, (u32_int)isr9);
    set_idt_gate(10, (u32_int)isr10);
    set_idt_gate(11, (u32_int)isr11);
    set_idt_gate(12, (u32_int)isr12);
    set_idt_gate(13, (u32_int)isr13);
    set_idt_gate(14, (u32_int)isr14);
    set_idt_gate(15, (u32_int)isr15);
    set_idt_gate(16, (u32_int)isr16);
    set_idt_gate(17, (u32_int)isr17);
    set_idt_gate(18, (u32_int)isr18);
    set_idt_gate(19, (u32_int)isr19);
    set_idt_gate(20, (u32_int)isr20);
    set_idt_gate(21, (u32_int)isr21);
    set_idt_gate(22, (u32_int)isr22);
    set_idt_gate(23, (u32_int)isr23);
    set_idt_gate(24, (u32_int)isr24);
    set_idt_gate(25, (u32_int)isr25);
    set_idt_gate(26, (u32_int)isr26);
    set_idt_gate(27, (u32_int)isr27);
    set_idt_gate(28, (u32_int)isr28);
    set_idt_gate(29, (u32_int)isr29);
    set_idt_gate(30, (u32_int)isr30);
    set_idt_gate(31, (u32_int)isr31);

    set_idt(); // Load with ASM
}

/* To print the message which defines every exception */
char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isr_handler(registers_t r)
{
	k_print("received interrupt: ");
	char str[3];
	int_to_asci(r.int_no, str);
	k_print(str);
	k_print("\n");
	k_print(exception_messages[r.int_no]);
	k_print("\n");
}