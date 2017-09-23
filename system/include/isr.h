#include "../../drivers/common.h"

typedef struct registers
{
	u32_int ds;
	u32_int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	u32_int int_no, err_code;
	u32_int eip, cs, eflags, useresp, ss;
} registers_t;