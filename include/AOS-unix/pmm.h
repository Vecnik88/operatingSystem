#ifndef PMM_H
#define PMM_H

#include <stdint.h>

typedef uint32_t phys_addr;
/* инициализирует физический менеджер памяти */
extern void pmm_init(size_t, phys_addr);
/* инициализирует регион размером size_t с адреса phys_addr */
extern void pmm_init_region(size_t, phys_addr);
/* деинициализирует регион */
extern void pmm_deinit_region(size_t, phys_addr);
/* выделяем 1 блок памяти(4096 байт) */
extern void *pmm_alloc_block();
/* освобождаем 1 блок памяти */
extern void pmm_free_block(void *);
/* выделяем регион памяти */
extern void *pmm_alloc_blocks(size_t);
/* освобождаем регион памяти */
extern void pmm_free_blocks(void *, size_t);
/* возвращает размер памяти */
extern size_t pmm_get_memory_size();
/* возвращает кол-во используемых блоков */
extern uint32_t pmm_get_use_block_count();
/* возвращает количество свободных блоков */
extern uint32_t pmm_get_free_block_count();
/* возвращает максимальное количество блоков */
extern uint32_t pmm_get_block_count();
/* возвращает размер одного блока */
extern uint32_t pmm_get_block_size();
/* включаем пейджинг */
extern void pmm_paging_enable(bool);
/* проверяем включен ли пейджинг */
extern bool pmm_is_paging();
/* загружаем директорию страниц в cr3 */
extern void pmm_load_PDBR(phys_addr);
/* возвращает физический адрес директорий страниц */
extern phys_addr pmm_get_PDBR();
#endif	/* PMM_H */