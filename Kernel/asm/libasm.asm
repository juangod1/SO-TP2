GLOBAL cpuVendor
GLOBAL initialize_stack_frame
GLOBAL get_eip
GLOBAL clear_interrupts
GLOBAL set_interrupts
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

%macro pushaqlite 0
    push rbx
    push rcx
    push rdx
    push rbp
    push rdi
    push rsi
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
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
	pop rbx
	mov rcx, rsp 
	mov rsp, rsi
	push 0x0
	push rsi 
	push 0x202 
	push 0x08 
	push rdi
	push 0x0 
	pushaqlite
	mov rax, rsp
	mov rsp, rcx
	push rbx 
	ret

get_eip:
	pop rax
	ret

clear_interrupts:
	cli
	ret

set_interrupts:
	sti
	ret