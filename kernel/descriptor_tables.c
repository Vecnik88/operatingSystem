#include "port.h"
#include "descriptor_tables.h"

extern void gdt_flush(u32_int);
extern void idt_flush(u32_int);

// Internal function prototypes.
static void init_gdt();
static void init_idt();
static void idt_set_gate(u8_int, u32_int, u16_int, u8_int);
static void gdt_set_gate(s32_int, u32_int, u32_int, u8_int, u8_int);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void init_descriptor_tables()
{
    init_gdt();
    init_idt();
}

static void init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base  = (u32_int)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_flush((u32_int)&gdt_ptr);
}

static void gdt_set_gate(s32_int num, u32_int base, u32_int limit, u8_int access, u8_int gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

static void init_idt()
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (u32_int)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

    idt_set_gate( 0, (u32_int)isr0 , 0x08, 0x8E);
    idt_set_gate( 1, (u32_int)isr1 , 0x08, 0x8E);
    idt_set_gate( 2, (u32_int)isr2 , 0x08, 0x8E);
    idt_set_gate( 3, (u32_int)isr3 , 0x08, 0x8E);
    idt_set_gate( 4, (u32_int)isr4 , 0x08, 0x8E);
    idt_set_gate( 5, (u32_int)isr5 , 0x08, 0x8E);
    idt_set_gate( 6, (u32_int)isr6 , 0x08, 0x8E);
    idt_set_gate( 7, (u32_int)isr7 , 0x08, 0x8E);
    idt_set_gate( 8, (u32_int)isr8 , 0x08, 0x8E);
    idt_set_gate( 9, (u32_int)isr9 , 0x08, 0x8E);
    idt_set_gate(10, (u32_int)isr10, 0x08, 0x8E);
    idt_set_gate(11, (u32_int)isr11, 0x08, 0x8E);
    idt_set_gate(12, (u32_int)isr12, 0x08, 0x8E);
    idt_set_gate(13, (u32_int)isr13, 0x08, 0x8E);
    idt_set_gate(14, (u32_int)isr14, 0x08, 0x8E);
    idt_set_gate(15, (u32_int)isr15, 0x08, 0x8E);
    idt_set_gate(16, (u32_int)isr16, 0x08, 0x8E);
    idt_set_gate(17, (u32_int)isr17, 0x08, 0x8E);
    idt_set_gate(18, (u32_int)isr18, 0x08, 0x8E);
    idt_set_gate(19, (u32_int)isr19, 0x08, 0x8E);
    idt_set_gate(20, (u32_int)isr20, 0x08, 0x8E);
    idt_set_gate(21, (u32_int)isr21, 0x08, 0x8E);
    idt_set_gate(22, (u32_int)isr22, 0x08, 0x8E);
    idt_set_gate(23, (u32_int)isr23, 0x08, 0x8E);
    idt_set_gate(24, (u32_int)isr24, 0x08, 0x8E);
    idt_set_gate(25, (u32_int)isr25, 0x08, 0x8E);
    idt_set_gate(26, (u32_int)isr26, 0x08, 0x8E);
    idt_set_gate(27, (u32_int)isr27, 0x08, 0x8E);
    idt_set_gate(28, (u32_int)isr28, 0x08, 0x8E);
    idt_set_gate(29, (u32_int)isr29, 0x08, 0x8E);
    idt_set_gate(30, (u32_int)isr30, 0x08, 0x8E);
    idt_set_gate(31, (u32_int)isr31, 0x08, 0x8E);

    idt_flush((u32_int)&idt_ptr);
}

static void idt_set_gate(u8_int num, u32_int base, u16_int sel, u8_int flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;

    idt_entries[num].flags   = flags /* | 0x60 */;
}
