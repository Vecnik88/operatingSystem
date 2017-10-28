#ifndef PRINT_K_H
#define PRINT_K_H

#include "vga.h"

#define ZEROPAD	1
#define SIGN	2
#define PLUS	4
#define SPACE	8
#define LEFT	16
#define SPECIAL	32
#define SMALL	64

#define isdigit(x)		((x) >= '0' && (x) <= '9')
#define isxdigit(x) 	(((x) >= '0' && (x) <= '9') || \
							((x) >= 'a' && (x) <= 'f') || \
								((x) >= 'A' && (x) <= 'F'))
#define islower(x) 	((x) >= 'a' && (x) <= 'z')
#define toupper(x) 		((x) >= 'a' && (x) <= 'z') ? ((x)-'a'+'A') : (x)

int printk(const char* fmt,...);

#endif