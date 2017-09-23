#include "../drivers/include/monitor.h"

int main() {
	u32_int value = 12345678;
	char hello[20] = "\nHELLO BRO\n";
	monitor_clear();
	monitor_write("hello Bro\n");
	monitor_write_hex(value);
	monitor_write(hello);
	monitor_write_dec(1234);
}