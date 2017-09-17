#ifndef MONITORH
#define MONITORH

#include "common.h"

void monitor_put(char c);				// <---. выводит символ на экран
void monitor_clear();					// <---. очищает экран
void monitor_write(char* c);			// <---. выводит символы на экран
void monitor_write_hex(uint32_t n);		// <---. выводит десятичное число в 16-ти ричном формате
void monitor_write_dec(uint32_t n);		// <---. выводит  десятичное число в 8-ми ричном формате

#endif