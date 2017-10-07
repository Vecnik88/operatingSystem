#ifndef MEM_H
#define MEM_H

#include "../cpu/types.h"

void mem_cpy(s8_int* src, s8_int* dst, u32_int count);
void mem_set(s8_int* dst, u8_int value, u32_int len);

#endif