;libasm.asm

GLOBAL start_VM_Driver


section .text

start_VM_Driver:
	push rbp
	mov rbp, rsp
	int 0x82
	mov [rdx], rax		;por que esto? era por el tp anterior para mandarle al start_shell()
	mov [rdx + 4], rbx	;los tamanios de la pantalla creo
	mov rax, rdx
	mov rsp, rbp
	pop rbp
	ret

