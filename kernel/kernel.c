#include "../drivers/include/monitor.h"
#include "../drivers/include/common.h"

void main()
{
	monitor_clear();
	monitor_write("Hello, world!");
}