#include "../drivers/ports.h"
#include "../drivers/monitor.h"
/* start kernel */
void main(void)
{
 	clear_screen();
    k_print_at("X", 1, 6);
    k_print_at("This text spans multiple lines", 75, 10);
    k_print_at("There is a line\nbreak", 0, 20);
    k_print("There is a line\nbreak");
    k_print_at("What happens when we run out of space?", 45, 24);
}