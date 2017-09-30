#include "../drivers/monitor.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

/* start function in my kernel */
void main() 
{
	clear_monitor();
	k_print("Hello Anton\n");
	k_print("skldlaksdlasklfkasl;fas");
	k_print_dec(1234);
	k_print_hex(1234);
	k_print("Hello Anton\n");
	k_print("skldlaksdlasklfkasl;fas");
	k_print("Hello Anton\n");
	k_print("skldlaksdlasklfkasl;fas");
	isr_install();
	__asm__ __volatile__ ("int $2");
	__asm__ __volatile__ ("int $3");
	__asm__ __volatile__ ("int $4");
	//__asm__ __volatile__ ("int $5");
	//__asm__ __volatile__ ("int $6");
	//__asm__ __volatile__ ("int $7");
	//__asm__ __volatile__ ("int $8");
	//__asm__ __volatile__ ("int $9");
	//__asm__ __volatile__ ("int $10");
	//__asm__ __volatile__ ("int $11");
	//__asm__ __volatile__ ("int $12");
	//__asm__ __volatile__ ("int $12");
	//__asm__ __volatile__ ("int $14");
	//__asm__ __volatile__ ("int $15");
	//__asm__ __volatile__ ("int $16");
	//__asm__ __volatile__ ("int $17");
	//__asm__ __volatile__ ("int $18");
	//__asm__ __volatile__ ("int $19");
	//__asm__ __volatile__ ("int $20");
	//__asm__ __volatile__ ("int $21");
	//__asm__ __volatile__ ("int $22");
	//__asm__ __volatile__ ("int $23");
}