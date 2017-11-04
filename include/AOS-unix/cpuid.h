#ifndef CPUID_H
#define CPUID_H

#define MAGIC_AMD	0x68747541
#define MAGIC_INTEL 0x756e6547

#define cpuid(in, a, b, c, d) asm volatile("cpuid": "=a" (a), "=b" (b), \
										   "=c" (c), "=d" (d) : "a" (in));

int print_info_cpu(void);
int print_intel(void);
int print_amd(void);
void print_regs(int eax, int ebx, int ecx, int edx);

#endif	/* CPUID_H */