/* Точка входа в наше ядро на С */

#include "screen.h"

int main()
{
	clear_screen();
	write_screen("AOS load...\n");
	asm volatile ("int $0x3");
	asm volatile ("int $0x4");
	write_screen("Hello user\n");
}