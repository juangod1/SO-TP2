
%macro pushState 0
	push rax
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

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro cleanRegs 0
	xor r15,r15
	xor r14,r14
	xor r13,r13
	xor r12,r12
	xor r11,r11
	xor r10,r10
	xor r9,r9
	xor r8,r8
	xor rsi,rsi
	xor rdi,rdi
	xor rbp,rbp
	xor rdx,rdx
	xor rcx,rcx
	xor rbx,rbx
	xor rax,rax
%endmacro