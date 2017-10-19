#ifndef DESCRIPTOR_TABLE_H
#define DESCRIPTOR_TABLE_H

#include "types.h"

void init_descriptor_table();

struct gdt_entry_struct
{
    u16_int limit_low;           /* младшие 16 бит граничного значения limit */
    u16_int base_low;            /* младшие 16 бит адреса */
    u8_int  base_middle;         /* следующие 8 бит адреса */
    u8_int  access;              /* флаги доступа, определяющие в каком кольце доступа сегмент */
    u8_int  granularity;
    u8_int  base_high;           /* последние 8 бит адреса */
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
   u16int limit;               /* верхние 16 битов всех предельных значений селектора */
   u32int base;                /* адрес первой структуры gdt_entry_t */
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;



#endif