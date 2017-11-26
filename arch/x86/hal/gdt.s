[global gdt_flush]

gdt_flush:
	mov eax, [esp + 4]	; берем переданные значения со стека(указатель на таблицу gdt)
	lgdt [eax]			; загружаем таблицу gdt
	mov ax, 0x10		; указываем значение кода данных ядра
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.flush 	; изменяем таким образом сегмент кода и переходим к выполнению кода ядра
.flush:
	ret

[global idt_flush]
idt_flush:
	mov eax, [esp + 4]
	lidt [eax]
	ret
