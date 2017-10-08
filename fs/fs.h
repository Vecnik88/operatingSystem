#ifndef FS_H
#define FS_H

#include "../cpu/types.h"

#define FS_CHARDEVICE 0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPe 0x05
#define FS_SYMLINK 0x06
#define FS_MOUNTPOINT 0x08		/* файл является активной точкой монтирования? */
/*
 * read_type_t, write_type_t, 
 * open_type_t, close_type_t
 * это указатели на функции
 */
typedef struct fs_node {
	s8_int name[128];			/* имя файла */
	u32_int mask;				/* маска прав доступа */
	u32_int uid;				/* пользователь, владеющий файлом */
	u32_int gid;				/* группа владеющая файлом */
	u32_int flags;				/* тип нода(директория, файл) */
	u32_int length;				/* размер файла в байтах */
	u32_int inode;				/* зависит от устройства, позволяет файловой системе идентифицировать файлы */
	u32_int impl;				/* номер, зависящий от реализации */
	read_type_t read;
	write_type_t write;
	open_type_t open;
	close_type_t close;
	readdir_type_t readdir;
	finddir_type_t finddir;
	struct fs_node* ptr;		/* используется для точек монтирования и символических ссылок */
} fs_node_t;

struct dirent {
	s8_int name[128];			/* имя файла */
	u32_int ino;				/* номер inode */
};

typedef u32_int (*read_type_t)(struct fs_node*, u32_int, u32_int, u8_int);
typedef u32_int (*write_type_t)(struct fs_node*, u32_int, u32_int, u8_int);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent* (*read_type_t)(struct fs_node*, u32_int);
typedef struct fs_node* (*finddir_type_t)(struct fs_node*, s8_int* name);

extern fs_node_t* fs_root;		/* корневой нод файловой системы */

u32_int read_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer);
u32_int write_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer);
u32_int open_fs(fs_node_t* node, u8_int read, u8_int write);
u32_int close_fs(fs_node_t* node);

struct dirent* readdir_fs(fs_node_t* node, u32_int index);
fs_node_t* finddir_fs(fs_node_t* node, s8_int* name);

#endif