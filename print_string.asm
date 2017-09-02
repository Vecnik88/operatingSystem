print_string:
	pusha
cicle:
	mov ah, 0x0e
	mov al, [bx]
	cmp al, 0
	je return
	int 0x10
	add bx, 1
	jmp cicle

return:
	popa
	ret