[org 0x7c00]
mov ah, 0x0e

mov bx, 30

cmp bx, 4
jle less_eq
cmp bx, 40
jl less
jmp other

less_eq:
	mov al, 'A'
	int 0x10
	jmp loop

less:
	mov al, 'B'
	int 0x10
	jmp loop

other:
	mov al, 'C'
	int 0x10

loop:
	jmp loop

times 510 -($-$$) db 0
dw 0xaa55