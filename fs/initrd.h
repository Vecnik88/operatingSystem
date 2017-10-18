#ifndef INITRD_H
#define INITRD_H

#include "../cpu/types.h"
#include "fs.h"

typedef struct {
    u32_int nfiles;			/* число файлов в ramdisk */
} initrd_header_t;

typedef struct
{
    u8_int magic;     		/* магическое число для проверки ошибок */
    s8_int name[64];  		/* имя файла */
    u32_int offset;   		/* смещение в initrd, указывающее откуда начинается файл */
    u32_int length;   		/* длина файла */
} initrd_file_header_t;

/*
	Инициализация initial ramdisk. Ему передается адрес модуля module,
	а возвращается нод созданной файловой системы.
 */

fs_node_t* initialise_initrd(u32_int location);

#endif