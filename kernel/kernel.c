#include "../drivers/include/monitor.h"

void main()
{
	monitor_clear();
	monitor_write("hello");
	//asm volatile ("int $0x3");
	//asm volatile ("int $0x4");
}