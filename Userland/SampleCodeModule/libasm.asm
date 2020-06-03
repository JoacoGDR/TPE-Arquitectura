;libasm.asm

GLOBAL start_VM_Driver
GLOBAL syscall_read
GLOBAL syscall_write


section .text

start_VM_Driver:
	push rbp
	mov rbp, rsp
	int 0x82
	mov [rdx], rax		;por que esto? era por el tp anterior para mandarle al start_shell()   era rax y rbx
	mov [rdx + 4], rbx	;los tamanios de la pantalla creo
	mov rax, rdx
	mov rsp, rbp
	pop rbp 
	ret

syscall_write:
    push rbp
    mov rbp, rsp 
    push rax
    push rbx
    push rcx
    push rdx
    mov rax, 0
    mov rbx, 0
    mov rcx, 0
    mov rdx, 0

    mov rax, 4
    mov rbx, 1
    mov rcx, rdi ; le paso el string
    mov rdx, rsi ; le paso la longitud del string
    int 80h

    pop rdx
    pop rcx
    pop rbx
    pop rax
    mov rsp, rbp
    pop rbp
    ret


syscall_read:
    push rbp
    mov rbp, rsp 
    push rax
    push rbx
    push rcx
    push rdx
    mov rax, 0
    mov rbx, 0
    mov rcx, 0
    mov rdx, 0

    mov rax, 3 	   ;ID
    mov rbx, rdi  ; le paso el file_descriptor
    mov rcx, rsi  ; le paso la direccion de donde tiene que guardar lo leido
    mov rdx, rdx  ; le paso la cantidad de caracteres que tiene que leer
    int 80h

    pop rdx
    pop rcx
    pop rbx
    pop rax
    mov rsp, rbp
    pop rbp
    ret


