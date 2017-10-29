%macro ISR_NOERRCODE 1
[global isr%1]		; %1 доступ к первому параметру
isr%1:
	cli					; запрещаем все прерывания
	push byte 0			; помещаем в стек фиктивный код ошибки
	push byte %1		; помещаем в стек номер прерывания (0)
	jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
[global isr%1]
isr%1:
	cli
	push byte %1
	jmp isr_common_stub
%endmacro

; вызовы макрофункций
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

; определена в isr.c
[extern isr_handler]

isr_common_stub:
	pusha

	mov ax, ds
	push eax

	mov ax, 0x10		; загрузка сегмента данных ядра
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	call isr_handler

	pop eax				; перезагрузка оригинального дескриптора сегмента данных
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	popa				; выталкиваем из стека значения edi, esi, ebp
	add esp, 8			; очищаем из стека код ошибки, помещаем в стек номер ISR
	sti
	iret				; выталкиваем из стека след. пять значений: CS, EIP, EFLAGS, SS, ESP