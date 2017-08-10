global loader						; символ входа для ELF

extern kmain

MAGIC_NUMBER equ 0x1BADB002				; определяем значение магического числа	
FLAGS equ 0x0						; определяем флаги мультизагрузки
CHECKSUM equ -MAGIC_NUMBER				; рассчитываем контрольную сумму
KERNEL_STACK_SIZE equ 4096				; размер стека

section .bss
align 4							; выравнивание на 4 байта
kernel_stack:						; метка указывает на начало памяти
	resb KERNEL_STACK_SIZE				; создаем стек для памяти ядра

section .text:						; начало раздела текста( кода )
align 4							; выравниваем код на величину 4 байта( для х86 )
	dd MAGIC_NUMBER					; записываем значение магического числа в код
	dd FLAGS					; записываем флаги
	dd CHECKSUM					; записываем контрольную сумму

loader:							; метка загрузчика( определяется как точка входа в среде компоновщика )
	mov eax, 0xCAFEBABE				; помещаем число в регистр еах

higher_half:

	mov esp, kernel_stack + KERNEL_STACK_SIZE	; регистр esp указывает на начало стека( конец памяти ) 

enter_kmain:

	call kmain					; вызываем функцию kmain

.loop:
	jmp .loop					; вечный цикл
