GLOBAL cpuVendor
GLOBAL getKey
GLOBAL saveRegisters
GLOBAL hours
GLOBAL minutes
GLOBAL seconds
GLOBAL getValue




section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret



;deberia empezar con cli (para no ser interrumpido), y luego hacer sti para habilitar nuevas interrupciones
;ahora bien, el getKey esta preguntando todo el dia, entonces queremos que sea interrumpida. 
getKey:
	push rbp
	mov rbp, rsp
	mov rax,0
	sti
loop:    
	in al,0x64       
    mov cl,al
    and al,0x01       
    cmp al,0
    je loop
    
    in al,0x60 

	;cmp al, 0x81
	;jl .fin
	;jmp loop

.fin:
;	cli  

	mov rsp, rbp
	pop rbp
	ret

;La hora(o minutos o segundos, depende lo que yo quiera) viene con este formato: 0001 0010  -> eso es 12
seconds:
    push rbp
    mov rbp, rsp

    mov al, 0        ;si quiero los segundos pono 0, minutos 2, horas 4

    call getValue  ;nos deja en al el valor

    mov rsp, rbp
    pop rbp
    ret

minutes:
    push rbp
    mov rbp, rsp

    mov al, 2        ;si quiero los segundos pono 0, minutos 2, horas 4

    call getValue  ;nos deja en al el valor

    mov rsp, rbp
    pop rbp
    ret

hours:
    push rbp
    mov rbp, rsp

    mov al, 4        ;si quiero los segundos pono 0, minutos 2, horas 4

    call getValue  ;nos deja en al el valor

    mov rsp, rbp
    pop rbp
    ret


getValue:
    push rbp
    mov rbp, rsp
    push rdx
    push rcx

    out 70h, al    ;sera 0, 2 o 4, le pido para leer
    in al, 71h  ;se hace la lectura

    mov dl, al    ;me guardo el valor de al
    and al, 00001111b ;me quedo con las unidades
    mov [value], al        ;me guardo las unidades

    mov al, dl        ;recupero lo que habia obtenido, asi puedo agarrar las decenas
    and al, 11110000b ;debo dividir por 16 asi obtengo el valor de las decenas

    shr al, 4  ;>> 4
    mov cl, 10
    mul cl        ;osea, multiplico el numero de decenas obtenido en al, por 10
    add [value], al        ;ya tenia unidades, ahora decenas + unidades = numero :)

    mov al, [value]        ;valor de retorno

    pop rcx
    pop rdx
    mov rsp, rbp
    pop rbp

    ret

section .bss
value resb 1000
