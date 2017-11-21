#include <AOS-unix/pmm.h>

#define PMMNGR_BLOCKS_PER_BYTE	8
#define PMMNGR_BLOCK_SIZE		4096
#define PMMNGR_BLOCK_ALIGN		PMMNGR_BLOCK_SIZE

/* размер физической памяти */
static uint32_t _mmngr_memory_size = 0;

/* количество используемых блоков */
static uint32_t _mmngr_used_blocks = 0;

/* максимальное количество доступных блоков памяти */
static uint32_t _mmngr_max_blocks = 0;

/* массив бит, который представляет блоки памяти */
static uint32_t * _mmngr_memory_map = 0;

/* устанавливаем бит */
inline void mmap_set(int bit)
{
	_mmngr_memory_map[bit/32] |= (1 << (bit % 32));
}

/* очищаем бит */
inline void mmap_unset()
{
	_mmngr_memory_map[bit/32] &= ~(1 << (bit % 32));
}

/* проверяем установку бита */
inline bool mmap_test(int bit)
{
	return _mmngr_memory_map[bit/32] & (1 << (bit % 32));
}

/* возвращает первый свободный блок */
int mmap_first_free()
{
	int i, j;
	for (i = 0; i < pmmngr_get_block_count()/32; ++i) {
		if (_mmngr_memory_map[i] != 0xffffffff) {
			for (j = 0; j < 32; ++j) {
				int bit = 1 << j;
				if (!(_mmngr_memory_map[i] & bit))
					return i * 4 * 8 + j;
			}
		}
	}

	return -1;
}

int mmap_first_free_s()
{
	
}
