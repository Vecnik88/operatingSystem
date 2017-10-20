; multiboot headers

MBOOT_PAGE_ALIGN    equ 1<<0				; загружает ядро на границу страницы
MBOOT_MEM_INFO      equ 1<<1				; предоставляет ядру информацию о памяти
MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[bits 32]

[global mboot]
[extern code]
[extern bss]
[extern end]

mboot:
	dd MBOOT_HEADER_MAGIC					; указывает, что ядро совместимо с multiboot
	dd MBOOT_HEADER_FLAGS					; указывает, как grub будет загружать наш файл(настройки)
	dd MBOOT_CHECKSUM						; для порядка

	dd mboot
	dd code
	dd bss
	dd end
	dd start

[global start]
[extern start_kernel]

start:
	push ebx								; загрузка указателя на место заголовка multiboot
	cli
	call start_kernel
	jmp $

