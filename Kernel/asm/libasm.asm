GLOBAL cpuVendor
GLOBAL initialize_stack_frame
GLOBAL get_eip
section .text

%macro PUSHAQ 0
	push gs
	push fs
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rsi
	push rdi
	push rbp
	push rdx
	push rcx
	push rbx
	push rax
%endmacro
	
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

initialize_stack_frame:
	mov rax, [rbp-8]
	push rax
	PUSHFQ
    PUSHAQ

get_eip:
	pop rax

