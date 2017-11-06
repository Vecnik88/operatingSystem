[global switch_page_directory]

switch_page_directory:
	push	ebp
	mov 	ebp, esp 
	mov		eax, [esp + 4] 
	mov		cr3, eax 
	mov		eax, cr0 
	or		eax, 0x80000000 
	mov		cr0, eax
	jmp $
	mov		esp, ebp 
	pop		ebp 
	ret