#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void mem_cpy(u8_int* src, u8_int* dst, u32_int count);
void mem_set(u8_int* dst, u8_int value, u32_int len);

#endif