print_string:
	pusha
start:
	mov al, [bx]
	cmp al, 0
	je return

	add bx, 1
	jmp start
	
return:
	popa
	ret