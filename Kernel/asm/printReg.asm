GLOBAL printRegs
GLOBAL os_dump_regs_again
EXTERN printReg
EXTERN printHex
EXTERN newLine

; -----------------------------------------------------------------------------
; printRegs -- print the values on the registers to the screen

printRegs:
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rsp
	push rbp
	push rdi
	push rsi
	push rdx
	push rcx
	push rbx
	push rax

	mov byte [os_dump_reg_stage], 0x00	; Reset the stage to 0 since we are starting
	mov rcx, rsp
	call newLine

os_dump_regs_again:
	mov rdi, os_dump_reg_string00
	mov rax,0 				; zeroing rax
	mov rbx,0 				; zeroing rbx
	mov al, [os_dump_reg_stage]
	mov bl, 5				; each string is 5 bytes
	mul bl					; ax = bl x al
	add rdi, rax 			; to reach desired string
	call printReg 			; Print the register name

	mov rax, [rcx]
	add rcx, 8
	call printHex

	add byte [os_dump_reg_stage], 1
	cmp byte [os_dump_reg_stage], 0x10
	jne os_dump_regs_again
	call newLine
	pop rax
	pop rbx
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	pop rbp
	pop rsp
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15

ret

os_dump_reg_string00: db '  A:', 0
os_dump_reg_string01: db '  B:', 0
os_dump_reg_string02: db '  C:', 0
os_dump_reg_string03: db '  D:', 0
os_dump_reg_string04: db ' SI:', 0
os_dump_reg_string05: db ' DI:', 0
os_dump_reg_string06: db ' BP:', 0
os_dump_reg_string07: db ' SP:', 0
os_dump_reg_string08: db '  8:', 0
os_dump_reg_string09: db '  9:', 0
os_dump_reg_string0A: db ' 10:', 0
os_dump_reg_string0B: db ' 11:', 0
os_dump_reg_string0C: db ' 12:', 0
os_dump_reg_string0D: db ' 13:', 0
os_dump_reg_string0E: db ' 14:', 0
os_dump_reg_string0F: db ' 15:', 0
os_dump_reg_stage: db 0x00
; -----------------------------------------------------------------------------

