;libasm.asm

GLOBAL start_VM_Driver
GLOBAL syscall_read
GLOBAL syscall_write
GLOBAL inforeg
GLOBAL get_temp

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


inforeg:
    push rbp
    mov rbp,rsp
    push rdi
    push rsi
    push rax
    push rbx

    ;;RAX;; distinto porque ya vengo con el numero.
    push rbx
    push rdi

    mov rdi, srax
    call syscall_write

    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;RBX;;
    push rbx
    push rdi

    mov rdi, srbx
    call syscall_write

    mov rax, rbx
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;RCX;;
    push rbx
    push rdi

    mov rdi, srcx
    call syscall_write

    mov rax, rcx
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;RDX;;
    push rbx
    push rdi

    mov rdi, srdx
    call syscall_write

    mov rax, rdx
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;RSI;;
    push rbx
    push rdi

    mov rdi, srsi
    call syscall_write

    mov rax, rsi
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;RDI;;
    push rbx
    push rdi

    mov rdi, srdi
    call syscall_write

    mov rax, rdi
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;RBP;;
    push rbx
    push rdi

    mov rdi, srbp
    call syscall_write

    mov rax, rbp
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;RSP;;
    push rbx
    push rdi

    mov rdi, srsp
    call syscall_write

    mov rax, rsp
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx
    
    ;;R8;;
    push rbx
    push rdi

    mov rdi, sr8
    call syscall_write

    mov rax, r8
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;R9;;
    push rbx
    push rdi

    mov rdi, sr9
    call syscall_write

    mov rax, r9
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;R10;;
    push rbx
    push rdi

    mov rdi, sr10
    call syscall_write

    mov rax, r10
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;R11;;
    push rbx
    push rdi

    mov rdi, sr11
    call syscall_write

    mov rax, r11
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;R12;;
    push rbx
    push rdi

    mov rdi, sr12
    call syscall_write

    mov rax, r12
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;R13;;
    push rbx
    push rdi

    mov rdi, sr13
    call syscall_write

    mov rax, r13
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

    ;;R14;;
    push rbx
    push rdi

    mov rdi, sr14
    call syscall_write

    mov rax, r14
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx


    ;;R15;;
    push rbx
    push rdi

    mov rdi, sr15
    call syscall_write

    mov rax, r15
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write
    pop rdi
    pop rbx

  
    
    
    pop rbx
    pop rax
    pop rsi
    pop rdi
    mov rsp,rbp
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

get_temp:
    push rbp
      mov rbp, rsp
    push rdi
    push rbx
    push rax

    mov rdi, temp
    call syscall_write
    mov rax, [0x19C]
    mov rbx, numstr
    call num_to_str
    mov rdi, rax ;primero imprimo rax
    call syscall_write
    mov rdi, ntr
    call syscall_write

    pop rax
    pop rbx
    pop rdi
    mov rsp,rbp
    pop rbp
    ;IA32_THERM_Status MSR_TEMEPRATURE_TARGET
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
;
;num_to_string:      ;acordate que el cociente de la division lo guarda en eax, el resto en edx, y el divisor en ecx
;	push rbp
;	mov rbp, rsp
;	push rbx
;	push rcx
;	push rdx
;
; ;   mov rax, rdi
;	mov rcx, 10             ;voy dividiendo de a 10
;	mov rdx, 0              ;inicializo en 0 para preparar la division pensando en EDX:EAX
; ;   mov rbx, numstr
;	add rbx, 9              ;me posiciono al final del string
;	mov byte [rbx], 0       ;cargo el 0 final del string
;	dec rbx
;.;sigo:
;	div rcx
;	add dl, 0x30           ;al sumarle 30 paso un valor numerico a su caracter ASCII
;	mov [rbx], dl
;	dec rbx
;	cmp rax, 0
;	je .termino
;	mov rdx, 0       ;lleno edx con cero ya que tengo que preparar la division pensando en EDX:EAX
;	jmp .sigo
;.;termino:
;	inc rbx       ;voy para adelante un espacio ya que ahora mismo estoy parado 1 posicion atras del numero
;	mov rax, rbx
;	pop rdx
;	pop rcx
;	pop rbx
;	mov rsp, rbp
;	pop rbp
;	ret
;;
;;
;;
;;    print_registers:
;;    push rbp
;;    mov rbp, rsp
;;    push rsp
;;    push rdx
;;    push rcx
;;    push rbx
;;    push rax
;;    push rdi
;;    push rsi
;;
;;     ;;;;RSI;;;;
;;    mov rdi, cadena_rsi
;;    mov rsi, 1
;;    call syscall_write
;;    pop rsi
;;    mov rdi, rsi
;;    call num_to_string
;;    mov rdi, rax
;;    call syscall_write
;;
;;    ;;;;RDI;;;;
;;    mov rdi, cadena_rdi
;;    mov rsi, 1
;;    call syscall_write
;;    pop rdi
;;    mov rdi, rdi
;;    call num_to_string
;;    mov rdi, rax
;;    call syscall_write
;;
;;    ;;;;RAX;;;;
;;    mov rdi, cadena_rax
;;    mov rsi, 1
;;    call syscall_write
;;    pop rax
;;    mov rdi, rax
;;    call num_to_string
;;    mov rdi, rax
;;    call syscall_write
;;
;;    ;;;;RBX;;;;
;;    mov rdi, cadena_rbx
;;    mov rsi, 1
;;    call syscall_write
;;    pop rbx
;;    mov rdi, rbx
;;    call num_to_string
;;    mov rdi, rax
;;    call syscall_write
;;
;;    ;;;;RCX;;;;
;;    mov rdi, cadena_rcx
;;    mov rsi, 1
;;    call syscall_write
;;    pop rcx
;;    mov rdi, rcx
;;    call num_to_string
;;    mov rdi, rax
;;    call syscall_write
;;
;;    ;;;;RDX;;;;
;;    mov rdi, cadena_rdx
;;    mov rsi, 1
;;    call syscall_write
;;    pop rdx
;;    mov rdi, rdx
;;    call num_to_string
;;    mov rdi, rax
;;    call syscall_write
;;
;;    ;;;;RSP;;;;
;;    mov rdi, cadena_rsp
;;    mov rsi, 1
;;    call syscall_write
;;    pop rsp
;;    push rsp
;;    mov rdi, rsp
;;    call num_to_string
;;    mov rdi, rax
;;    call syscall_write
;;
;;    ;;;;RBP;;;;
;;    mov rdi, cadena_rbp
;;    mov rsi, 1
;;    call syscall_write
;;    pop rbp
;;    push rbp
;;    mov rdi, rbp
;;    call num_to_string
;;    mov rdi, rax
;;    call syscall_write
;;
;;    mov rsp, rbp
;;    pop rbp
;;    ret
;;