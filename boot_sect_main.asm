[org 0x7c00]

mov bx, HELLO
call print

call print_n1

mov bx, GOODBYE
call print

call print_n1

mov dx, 0x12fe
call print_hex

jmp $

%include "boot_sect_print.asm"
%include "boot_sect_print_hex.asm"

HELLO:
	db 'Hello, Anton Mikaev. This is your first programm in assembler', 0

GOODBYE:
	db 'Goodbye, Programm off', 0

times 510-($-$$) db 0
dw 0xaa55