;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;									;;
;; boot.S 							;;
;;	- начало нашего ядра			;;
;;	- взаимодействует с загрузчиком	;;
;;	- заполняет стуктуру multiboot	;;
;;									;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

mboot_page_align 	equ 1<<0		; загружает ядро и модули на границу страницы
mboot_mem_info		equ 1<<1		; предоставить ядру информацию о памяти
mboot_header_magic	equ 0x1badb002	; указывает что ядро совместимо со стандартом multiboot

mboot_header_flags 	equ mboot_page_align | mboot_mem_info
mboot_checksum 		equ -(mboot_header_magic+mboot_header_flags)

[bits 32]
[global mboot]						; вызываем из кода на С
[extern code]						; начало секции .text
[extern bss]						; начало секции .bss
[extern end]						; конец последней вызываемой секции

mboot:
	dd	mboot_header_magic
	dd	mboot_header_flags			; указатель как GRUB должен загружать ядро
	dd	mboot_checksum
	dd  mboot 						; место размещения дескриптора
	dd  code						; начало секции '.text' (код) ядра, c него начинается выполнение ядра
	dd  bss							; начало секции '.data' ядра.
	dd  end							; конец ядра.
	dd  start						; точка входа в ядро (первоначальный EIP)

[global start]
[extern start_kernel]

start:
	push ebx						; загрузка указателя на multiboot
	cli
	call start_kernel
	jmp $