/* структура описывающая шлюз прерываний */
struct idt_entry_struct
{
	u16_int base_lo;		// младшие 16 битов адреса, куда проиходит переход в случае прерывания
	u16_int sel;			// переключатель сегмента ядра
	u8_int always0;			// всегда 0
	u8_int flags;			// флаги
	u16_int base_hi;		// старшие 16 битов адреса, куда происходит переход
} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;

struct idt_ptr_struct
{
	u16_int limit;
	u32_int base;
} __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;

struct gdt_entry_struct
{
	u16_int limit_low;
	u16_int base_low;
	u8_int base_middle;
	u8_int access;
	u8_int granularity;
	u8_int base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
	u16_int limit;
	u32_int base;
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

void init_descriptor_tables();

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
