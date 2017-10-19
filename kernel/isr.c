#include "isr.h"

void isr_handler(registers_t regs)
{
    write_screen("recieved interrupt: ");
    write_screen_dec(regs.int_no);
    monitor_put('\n');
}