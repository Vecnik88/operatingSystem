#include "../drivers/ports.h"
#include "../drivers/monitor.h"
/* start kernel */
void main(void)
{
	clear_screen();
	k_print_at("Hello! I am your kernel\n", -1, -1);
}