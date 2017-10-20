#ifndef ISR_H
#define ISR_H

#include "port.h"
#include "screen.h"

typedef struct registers
{
    u32_int ds;
    u32_int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32_int int_no, err_code;
    u32_int eip, cs, eflags, useresp, ss;
} registers_t;

#endif	/* ISR_H */