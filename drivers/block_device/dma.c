#include <AOS-unix/dma.h>
#include <AOS-unix/port.h>

void flpy_init_dma()
{
	out_byte(0x0a, 0x06);		// маскируем dma канал 2
	out_byte(0xd8, 0xff);		// сброс master flip-flop
	out_byte(0x04, 0);			// адрес = 0х1000
	out_byte(0x04, 010);
	out_byte(0xd8, 0xff);		// перезагрузка master flip-flop
	out_byte(0x05, 0xff);		// подсчитываем количество байтов на диске
	out_byte(0x05, 0x23);
	out_byte(0x80, 0);			// внешний регистр страницы = 0
	out_byte(0x0a, 0x02);		// unmask dma channel 2
}

void flpy_dma_read()
{
	out_byte(0x0a, 0x06);		// mask dma channel 2
	out_byte(0x0b, 0x56);		// чтение второго канала
	out_byte(0x0a, 0x02);		// unmask dma channel 2
}

void flpy_dma_write()
{
	out_byte(0x0a, 0x06);		// mask dma channel 2
	out_byte(0x0b, 0x5a);		// запись во второй канал
	out_byte(0x0a, 0x02);		// unmask dma channel 2
}