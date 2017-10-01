#include "../drivers/ports.h"
#include "../drivers/monitor.h"
/* start kernel */
void main(void)
{
	clear_screen();
	k_print("Hello! I am your kernel\n");
}