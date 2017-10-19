#ifndef PORT_H
#define PORT_H

#include "types.h"

void out_byte(u16_int port, u8_int value);
u8_int in_byte(u16_int port);
u16_int in_word(u16_int port);

#endif // PORT_H