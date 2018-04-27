
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _divideByZeroHandler
GLOBAL _overflowHandler
GLOBAL _opcodeHandler
GLOBAL _generalProtection

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN schedule
EXTERN printInt
SECTION .text

%include "./asm/macros.m"

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; first parameter
	mov rsi, rsp ; second parameter

	call exceptionDispatcher
	
	popState

	mov qword [rsp],0x400000
	iretq

%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_divideByZeroHandler:
	exceptionHandler 0

;Overflow Exception
_overflowHandler:
	exceptionHandler 4

;Opcode Exception
_opcodeHandler:
	exceptionHandler 6

_generalProtection:
	exceptionHandler 13

haltcpu:
	cli
	hlt
	ret



SECTION .bss
	aux resq 1

;no puedo backupear el ip en nasm, 
;vamos a tener que ver como solucionarlo
%macro POPAQ 0
	pop rax
	pop rbx
	pop rcx
	pop rdx
	pop rbp
	pop rdi
	pop rsi
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15
	pop fs
	pop gs
%endmacro



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



_tick_handler:
	PUSHAQ
	mov rdi,rsp
	;optionally change to kernel stack here for security reasons.
	call schedule 
	mov rsp, rax
	POPAQ
	mov al, 20h
	out 20h, al
	iretq