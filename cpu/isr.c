#include "isr.h"
#include "idt.h"
#include "../drivers/monitor.h"
#include "../kernel/util.h"
#include "../drivers/ports.h"

isr_t interrupt_handlers[256];

void isr_init()
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

    out_byte(0x20, 0x11);
    out_byte(0xA0, 0x11);
    out_byte(0x21, 0x20);
    out_byte(0xA1, 0x28);
    out_byte(0x21, 0x04);
    out_byte(0xA1, 0x02);
    out_byte(0x21, 0x01);
    out_byte(0xA1, 0x01);
    out_byte(0x21, 0x0);
    out_byte(0xA1, 0x0); 

    // Install the IRQs
    set_idt_gate(32, (u32_int)irq0);
    set_idt_gate(33, (u32_int)irq1);
    set_idt_gate(34, (u32_int)irq2);
    set_idt_gate(35, (u32_int)irq3);
    set_idt_gate(36, (u32_int)irq4);
    set_idt_gate(37, (u32_int)irq5);
    set_idt_gate(38, (u32_int)irq6);
    set_idt_gate(39, (u32_int)irq7);
    set_idt_gate(40, (u32_int)irq8);
    set_idt_gate(41, (u32_int)irq9);
    set_idt_gate(42, (u32_int)irq10);
    set_idt_gate(43, (u32_int)irq11);
    set_idt_gate(44, (u32_int)irq12);
    set_idt_gate(45, (u32_int)irq13);
    set_idt_gate(46, (u32_int)irq14);
    set_idt_gate(47, (u32_int)irq15);

    set_idt(); // Load with ASM
}

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

void isr_handler(registers_t r) {
    k_print("received interrupt: ");
    char s[3];
    i_t_o_a(r.int_no, s);
    k_print(s);
    k_print("\n");
    k_print(exception_messages[r.int_no]);
    k_print("\n");
}

void register_interrupt_handler(u8_int n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_t r) {
    /* After every interrupt we need to send an EOI to the PICs
     * or they will not send another interrupt again */
    if (r.int_no >= 40) 
    	out_byte(0xA0, 0x20); /* slave */
    
    out_byte(0x20, 0x20); /* master */

    /* Handle the interrupt in a more modular way */
    if (interrupt_handlers[r.int_no] != 0) {
        isr_t handler = interrupt_handlers[r.int_no];
        handler(r);
    }
}