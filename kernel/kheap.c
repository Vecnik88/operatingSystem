#include "kheap.h"

/* объявлено в скрипте линковщика */
extern u32_int end;

u32_int placement_address = (u32_int)&end;

u32int kmalloc_int(u32int sz, s32_int align, u32_int *phys)
{
    if (align == 1 && (placement_address & 0xFFFFF000) ) {
        placement_address &= 0xFFFFF000;
        placement_address += 0x1000;
    }
    if (phys)
    {
        *phys = placement_address;
    }
    u32_int tmp = placement_address;
    placement_address += sz;

    return tmp;
}

u32_int kmalloc_a(u32_int sz)
{
    return kmalloc_int(sz, 1, 0);
}

u32_int kmalloc_p(u32_int sz, u32_int *phys)
{
    return kmalloc_int(sz, 0, phys);
}

u32_int kmalloc_ap(u32_int sz, u32_int *phys)
{
    return kmalloc_int(sz, 1, phys);
}

u32_int kmalloc(u32_int sz)
{
    return kmalloc_int(sz, 0, 0);
}