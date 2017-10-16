#include "initrd.h"

/* Определяется интерфейс и структуры, используемые для диска initial ramdisk */

initrd_header_t* initrd_header;			/* Заголовок */
initrd_file_header_t* file_headers;		/* список заголовков файлов */
fs_node_t* initrd_root;					/* нод корневого директория */
fs_node_t* initrd_dev;					/* нод для /dev в нем монтируем файловую систему devfs */
fs_node_t* root_nodes;					/* список нодов файлов */
s32_int nroot_nodes;					/* количество нодов файлов */
struct dirent dirent;

static u32_int initrd_read(fs_node_t* node, u32_int offset, u32_int size, u8_int* buffer)
{
	initrd_file_header_t header = file_header[node->inode];
	if (offset > header.length)
		return 0;

	if (offset+size > header.length)
		size = header.length-offset;

	mem_cpy(buffer, (u8_int*)(header.offset+offset), size);

	return size;
}

static struct dirent* initrd_readdir(fs_node_t* node, u32_int index)
{
	if (node == initrd_root && index == 0) {
		strcpy(dirent.name, "dev");
		dirent.name[3] = '/0';
		dirent.ino = 0;

		return &dirent;
	}

	if (index-1 >= nroot_nodes)
		return 0;

	strcpy(dirent.name, root_nodes[index-1].name);
	dirent.name[strlen(root_nodes[index-1].name)] = '\0';
	dirent.ino = root_nodes[index-1].inode;

	return &dirent;
}

static fs_node_t* initrd_finddir(fs_node_t* node, s8_int* name)
{
	if (node == initrd_root && !strcmp(name, "dev"))
		return initrd_dev;

	s8_int i;
	for (i = 0; i < nroot_nodes; ++i)
		if (!strcmp(name, root_nodes[i].name))
			return &root_nodes[i];

	return 0;
}

fs_node_t* initialise_initrd(u32_int location)
{
	initrd_header = (initrd_header_t*) location;
	file_headers = (initrd_file_header_t *) (location+sizeof(initrd_header_t));

	/* инициализация корневого директория */
	initrd_root = (fs_node_t*)k_malloc(sizeof(fs_node_t));
	strcpy(initrd_root->name, "initrd");
	initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->length = 0;
	initrd_root-flags = FS_DIRECTORY;
	initrd_root->read = 0;
	initrd_root->write = 0;
	initrd_root->open = 0;
	initrd_root->close = 0;
	initrd_root->readdir = &initrd_readdir;
	initrd_root->finddir = &initrd_finddir;
	initrd_root->ptr = 0;
	initrd_root->impl = 0;

	/* инициализируем директорий /dev */
	initrd_dev = (fs_node_t*)k_malloc(sizeof(fs_node_t));
	strcpy(initrd_dev->name, "dev");
	initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
	initrd_dev->flags = FS_DIRECTORY;
	initrd_root->read = 0;
	initrd_root->write = 0;
	initrd_root->open = 0;
	initrd_root->close = 0;
	initrd_root->readdir = &initrd_readdir;
	initrd_root->finddir = &initrd_finddir;
	initrd_root->ptr = 0;
	initrd_root->impl = 0;

	root_nodes = (fs_node_t*)kmalloc(sizeof(fs_node_t) * initrd_header->nfiles);
	nroot_nodes = initrd_header->nfiles;

	s8_int i;
	for (i = 0; i < initrd_header->nfiles; ++i) {
		/* указываем смещение относительно начала памяти */
		file_headers[i].offset += location;
		strcpy(root_nodes[i].name, &file_headers[i].name);
		root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
		root_nodes[i].length = file_headers[i].length;
		root_nodes[i].inode = i;
		root_nodes[i].flags = FS_FILE;
		root_nodes[i].read = &initrd_read;
		root_nodes[i].write = 0;
		root_nodes[i].readdir = 0;
		root_nodes[i].finddir = 0;
		root_nodes[i].open = 0;
		root_nodes[i].close = 0;
		root_nodes[i].impl = 0;
	}

	return initrd_root;
}