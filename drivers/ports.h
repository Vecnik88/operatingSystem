#include "../cpu/types.h"

u8_int in_byte(u16_int port);					/* получаем байт из порта */
void out_byte(u16_int port, u8_int data);		/* отправляем байт в порт */
u16_int in_word(u16_int port);					/* получаем 2-байта из порта */
void out_word(u16_int port, u16_int data);		/* отправляем 2-байта в порт */