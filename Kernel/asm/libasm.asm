GLOBAL cpuVendor
GLOBAL getKey
GLOBAL saveRegisters
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




getKey:
	push rbp
	mov rbp, rsp
	mov rax,0
;	sti
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

