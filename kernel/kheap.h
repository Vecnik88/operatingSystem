#ifndef KHEAP_H
#define KHEAP_H

#include "port.h"

/**
   выделите кусок памяти, размером sz. Если align == 1,
   фрагмент должен быть выровнен по страницам. Если phys! = 0, физическое
   расположение выделенного фрагмента будет сохранено в физическом состоянии.

   Это внутренняя версия kmalloc. Более удобный
   представления параметров доступны в kmalloc, kmalloc_a,
   kmalloc_ap, kmalloc_p.
**/
u32_int kmalloc_int(u32_int sz, s32_int align, u32_int *phys);

u32int kmalloc_a(u32int sz);
u32int kmalloc_p(u32int sz, u32int *phys);
u32int kmalloc_ap(u32int sz, u32int *phys);
u32int kmalloc(u32int sz);

#endif /* KHEAP_H */