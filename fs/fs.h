#include FS_H
#define FS_H

#include "../cpu/types.h"

/* В Unix-подобной ОС, все есть файл, поэтому займемся описание флагов файлов */
#define FS_FILE			0x01
#define FS_DIRECTORY 	0x02
#define FS_CHARDEVICE 	0x03
#define FS_BLOCKDEVICE 	0x04
#define FS_PIPE 		0x05
#define FS_SYMLINC 		0x06
#define FS_MOUNTPOINT  	0x08

struct fs_node;

/* каллбэки наших функций, делаем согласно POSIX */
typedef u32int (*read_type_t)(struct fs_node*,u32_int,u32_int,u8_int*);
typedef u32int (*write_type_t)(struct fs_node*, u32_int, u32_int, u8_int*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent * (*readdir_type_t)(struct fs_node*,u32int);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name);

/* Файловую систему представим в виде НОДов */
typedef struct fs_node
{
    s8_int name[128];     	/* имя файла */
    u32_int mask;        	/* маска */
    u32_int uid;         	/* владелец файла */
    u32_int gid;         	/* группа владеющая файлом */
    u32_int flags;       	/* флаги говорящие о принадлежности файла */
    u32_int inode;       	/* идентифицирует тип нашей файловой системы */
    u32_int length;      	/* размер файла в байтах */
    u32_int impl;        	/* зависит от реализации */
    read_type_t read;
    write_type_t write;
    open_type_t open;
    close_type_t close;
    readdir_type_t readdir;
    finddir_type_t finddir;
    struct fs_node *ptr; 	/* точка монтирования */
} fs_node_t;

struct dirent {
	s8_int name[128];
	u32_int ino;			/* требуется для POSIX */
}

extern fs_node_t *fs_root;	/* корневой каталог, "/" - в Linux */

u32_int read_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer);
u32_int write_fs(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer);
void open_fs(fs_node_t* node, u8_int read, u8_int write);
void close_fs(fs_node_t* node);
struct dirent* readdir_fs(fs_node_t* node, u32_int index);
fs_node_t* finddir_fs(fs_node_t* node, s8_int* name);

#endif