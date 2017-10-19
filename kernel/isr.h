#ifndef ISR_H
#define ISR_H

#include "types.h"
#include "screen.h"

typedef struct registers
{
    u32_int ds;                  					/*селектор сегмента данных*/
    u32_int edi, esi, ebp, esp, ebx, edx, ecx, eax; /*регистры общего назначения*/
    u32_int int_no, err_code;    					/*прерывания*/
    u32_int eip, cs, eflags, useresp, ss;
} registers_t;

#endif