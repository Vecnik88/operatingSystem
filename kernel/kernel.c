#include "../drivers/include/common.h"
#include "../drivers/include/monitor.h"

void main()
{
	monitor_clear();
	monitor_write("Hello, world!");
}