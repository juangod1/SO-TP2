GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt
GLOBAL spoof_tick

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
EXTERN debug
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
	push rax
	pushaqlite
	mov rdi,rsp ;rsp of previous process
	call schedule
	mov rsp, rax ;set rsp to next process
	mov al, 20h
	out 20h, al
	popaqlite
	pop rax
	iretq

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


_tick_handler:
	pushaq
	mov rdi,rsp
	;optionally change to kernel stack here for security reasons.
	call schedule
	mov rsp, rax
	popaq
	mov al, 20h
	out 20h, al
	iretq

spoof_tick:
    int 0x20
    ret

SECTION .bss
	aux resq 1
