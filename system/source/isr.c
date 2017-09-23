#include "../../drivers/common.h"
#include "../include/isr.h"
#include "../../drivers/monitor.h"

void isr_handler(registers_t regs)
{
	monitor_write("received interrupt: ");
	monitor_write_dec(regs.int_no);
	monitor_put('\n');
}