/* Точка входа в наше ядро на С */

#include "screen.h"

int main()
{
	clear_screen();
	write_screen("AOS load...\n");
	write_screen("Hello user\n");
}