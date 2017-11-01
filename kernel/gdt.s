[global gdt_flush]		; позволяет коду на С обращаться к gdt_flush

gdt_flush:
	mov eax, [esp + 4]	; параметры передаются через стек
	lgdt [eax]			; загружаем новую таблицу gdt так как старую
						; за нас настраивал grub и мы о ней ничего не знаем

	mov ax, 0x10		; 0x10 является смещением, находящимся в таблице gdt
						; и указывает на сегмент данных

	mov ds, ax			; необходимо настроить все сегменты - как сегменты данных
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x08:.flush 	; 0x08 является смещением на наш сегмент кода
						; таким образом мы перезагруем наш cs регистр
.flush
	ret

[global idt_flush]
idt_flush:
	mov eax, [esp + 4]
	lidt [eax]
	ret