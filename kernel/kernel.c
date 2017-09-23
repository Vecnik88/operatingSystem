#include "../drivers/include/monitor.h"

void main()
{
	int i = 0;
	for(; i < 1000; ++i) {
		//monitor_clear();
		monitor_write("Hello, world!\n This is my operation system-x86\n");
	}
}