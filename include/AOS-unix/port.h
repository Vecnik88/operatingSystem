#ifndef PORT_H
#define PORT_H

#include <stdarg.h>
#include <stdint.h>

uint8_t in_byte(uint16_t port);
void out_byte(uint16_t port, uint8_t data);
uint16_t in_word(uint16_t port);
void out_word(uint16_t port, uint16_t data);

#endif