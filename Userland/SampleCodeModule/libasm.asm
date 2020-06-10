;libasm.asm

GLOBAL start_VM_Driver
GLOBAL syscall_read
GLOBAL syscall_write
GLOBAL syscall_clearView
GLOBAL inforeg
GLOBAL get_temp
GLOBAL get_brand

GLOBAL execute_opcode
section .text



execute_opcode:
    UD2

;recibe 0 o 1 como único parametro
start_VM_Driver:
	push rbp
	mov rbp, rsp
    push rax
    mov rax, rdi
	int 0x82
	
    pop rax
	mov rsp, rbp
	pop rbp 
	ret

change_screen:
    push rbp
    mov rbp, rsp
    int 0x80
    mov rsp, rbp
    pop rbp
    ret


get_brand:
   push rbp
   mov rbp, rsp
    push rdi
    push rsi
    push rax
    
    
    mov rax, 0
    xor rax, rax






   
 
XOR EAX,EAX
mov eax, 80000002h
    CPUID
    MOV dword  [name], eax
    MOV dword  [name+4], ebx
    MOV dword  [name+8], ecx
    MOV dword  [name+12], edx
 
    

    mov eax, 80000003h
    CPUID
    MOV dword  [name+16], eax
    MOV dword  [name+20], ebx
    MOV dword  [name+24], ecx
    MOV dword  [name+28], edx
 
    


    mov eax, 80000004h
    CPUID
    MOV dword  [name+32], eax
    MOV dword  [name+36], ebx
    MOV dword  [name+40], ecx
    MOV dword  [name+44], edx
 
    


    mov rdi, name 
    mov rsi, 48
    call syscall_write

    pop rax
    pop rsi
    pop rdi
    mov rsp, rbp
    pop rbp
    ret








inforeg:
    push rbp
    mov rbp, rsp 
    push rax
    push rbx
    push rcx
    push rdx
    
    mov rax, 2
    mov rbx, 1
    mov rcx, 0 ; no lo uso..
    mov rdx, 0 ; no lo uso.. 
    int 80h

    pop rdx
    pop rcx
    pop rbx
    pop rax
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
    mov rdx, 0 ; no se usa..
    int 80h

    pop rdx
    pop rcx
    pop rbx
    pop rax
    mov rsp, rbp
    pop rbp
    ret

syscall_clearView: 
    push rbp
    mov rbp, rsp 
    push rax
    push rbx
    push rcx
    push rdx

    mov rcx, 0
    mov rdx, 0

    mov rax, 6
    mov rbx, 1
    int 80h

    pop rdx
    pop rcx
    pop rbx
    pop rax
    mov rsp, rbp
    pop rbp
    ret



get_temp:
    push rbp
    mov rbp, rsp
    push rdi
    push rbx
    push rax
    push rdx
    push rcx

    mov rdx, [1A2h] ;en este registro saco los bits 23 a 16
    and rdx, 0xFF0000
    sar rdx, 16
    mov rcx, [19Ch] ;en este registro saco los bits 22 a 16
    and rcx, 0x7F0000
    sar rcx, 16

    sub rdx, rcx
    mov rax, rdx
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write

    pop rcx
    pop rdx
    pop rax
    pop rbx
    pop rdi
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



num_to_str: ;en rax tengo mi numero
    push rbp
    mov rbp, rsp ;genero stackframe
    push rcx
    push rdx
    push rbx

    mov rcx, 10
    mov rdx, 0

    add rbx, 99999 ;me voy hasta al final de mi string reservado
    mov byte [rbx], 0 ;y pongo un 0

.sigo:
    dec rbx     ; me muevo uno para la izquierda
    div rcx ;divide rax por rcx y guarda el resto en edx
    add dl, 0x30 ;le sumo al resto el ascii '0'
    mov [rbx], dl
    cmp rax, 0 ;si el cociente entero me da 0 entonces terminé
    je .termino
    mov rdx, 0 ;piso edx con 0 devuelta
    jmp .sigo
.termino:

    mov rax, rbx
    pop rbx
    pop rdx
    pop rcx
    mov rsp, rbp
    pop rbp
    ret

section .bss
numstr resb 100000
name resb 100

section .data

    temp db "La temperatura de la PC :",0
    ntr db "", 10,0
    srax db "rax: ", 0
    srbx db "rbx: ", 0
    srcx db "rcx: ", 0
    srdx db "rdx: ", 0
    srsi db "rsi: ", 0
    srdi db "rdi: ", 0
    srbp db "rbp: ", 0
    srsp db "rsp: ", 0
    sr8 db "r8: ", 0
    sr9 db "r9: ", 0
    sr10 db "r10: ", 0
    sr11 db "r11: ", 0
    sr12 db "r12: ", 0
    sr13 db "r13: ", 0
    sr14 db "r14: ", 0
    sr15 db "r15: ", 0
;
;
;  1A2 -> bits 23:16 TEMPERATURE TARGET 
;  1A2 -> bits 29:24 TEMPERATURE OFFESET
; si se suman los dos anteriores se consigue la temperatura
; de alerta.

;  19C -> 22-16 DIGITAL READOUT (Delta)
; (delta) = -PC_TEMP + TEMP_ALERTA
;  TEMP_ALERTA - (delta)  = PC_TEMP
;
;
