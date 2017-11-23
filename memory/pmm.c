#include <AOS-unix/pmm.h>

#define PMM_BLOCKS_PER_BYTE	8
#define PMM_BLOCK_SIZE		4096
#define PMM_BLOCK_ALIGN		PMM_BLOCK_SIZE

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

int mmap_first_free_s(size_t size)
{
	if (size == 0)
		return 0;

	if (size == 1)
		return mmap_first_free();

	int i, j, count;
	for (i = 0; i < pmm_get_block_count()/32; ++i) {
		if (_mmngr_memory_map[i] != 0xffffffff) {
			for (j = 0; j < 32; ++j) {
				int bit = 1 << j;
				if (!(_mmngr_memory_map[i] & bit)) {
					int starting_bit = i * 32;
					starting_bit += bit;
					uint32_t free = 0;

					for (count = 0; count <= size; ++count) {
						if (!mmap_test(starting_bit + count))
							++free;
						if (free == size)
							return i * 4 * 8 + j;
					}
				}
			}
		}
	}

	return -1;
}

void pmm_init_region(size_t mem_size, phys_addr bitmap)
{
	_mmngr_memory_size = mem_size;
	_mmngr_memory_map = (uint32_t *)bitmap;
	_mmngr_max_blocks = (pmm_get_memory_size() * 1024)/PMM_BLOCK_SIZE;
	_mmngr_used_blocks = _mmngr_max_blocks;

	memset(_mmngr_memory_map, 0xf, pmm_get_block_count()/PMM_BLOCKS_PER_BYTE);
}

void pmm_init_region(phys_addr base, size_t size)
{
	int align = base/PMM_BLOCK_SIZE;
	int blocks = size/PMM_BLOCK_SIZE;

	for (; blocks >= 0; --blocks) {
		mmap_unset(align++);
		_mmngr_used_blocks--;
	}

	mmap_unset(0);
}

void *pmm_allock_block()
{
	if (pmm_get_free_block_count() <= 0)
		return 0;

	int frame = mmap_first_free();

	if (frame == -1)
		return 0;

	mmap_set(frame);
	phys_addr addr = frame * PMM_BLOCK_SIZE;
	_mmngr_used_blocks++;

	return (void *)addr;
}

void pmm_free_block(void *p)
{
	phys_addr addr = (phys_addr)p;
	int frame = addr/PMM_BLOCK_SIZE;
	mmap_unset(frame);

	_mmngr_used_blocks--;
}

void *pmm_allock_block(size_t size)
{
	if (pmm_get_free_block_count() <= size)
		return 0;

	int frame = mmap_first_free_s(size);

	if (frame == -1)
		return 0;

	int i;
	for (i = 0, i < size; ++i)
		mmap_set(frame + i);

	phys_addr addr = frame * PMM_BLOCK_SIZE;
	_mmngr_used_blocks += size;

	return (void *)addr;
}

void pmm_free_blocks(void *p, size_t size)
{
	phys_addr addr = (phys_addr)p;
	int frame = addr/PMM_BLOCK_SIZE;

	int i;
	for (i = 0; i < size; ++i)
		mmap_unset(frame + i);

	_mmngr_used_blocks -= size;
}

size_t pmm_get_memory_size()
{
	return _mmngr_memory_size;
}

uint32_t pmmngr_get_block_count()
{
	return _mmngr_max_blocks;
}

uint32_t pmm_get_use_block_count()
{
	return _mmngr_used_blocks;
}

uint32_t pmm_get_free_block_count()
{
	return _mmngr_max_blocks - _mmngr_used_blocks;
}

uint32_t pmm_get_block_size()
{
	return PMMNGR_BLOCK_SIZE;
}

void pmm_paging_enable(phys_addr addr)
{
   asm volatile("mov %%0, %%cr3":: "r"(addr));
   uint32_t cr0;
   asm volatile("mov %%cr0, %0": "=r"(cr0));
   cr0 |= 0x80000000; // Enable paging!
   asm volatile("mov %0, %%cr0":: "r"(cr0));
}
