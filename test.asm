[org 0x7c00]
mov bx, HELLO_MSG
call print_string

mov bx, GOODBYE_MSG
call print_string

loop:
	jmp loop

%include "print_string.asm"

HELLO_MSG:
	db 'Hello Anton, is your programm in assembler', 0

GOODBYE_MSG:
	db 'GOODBYE Anton, is your programm in assembler', 0

times 510-($-$$) db 0
dw 0xaa55