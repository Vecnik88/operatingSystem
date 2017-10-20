#include "isr.h"

void isr_handler(registers_t regs)
{
    screen_write("recieved interrupt: ");
    //screen_write_dec(regs.int_no);
    screen_write("\n");
}