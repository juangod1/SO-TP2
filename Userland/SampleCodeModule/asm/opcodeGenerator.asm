GLOBAL opcodeGenerator
GLOBAL _div0

section .text

opcodeGenerator:
	ud2
	ret

_div0:
	mov rcx, 0
	div rcx
	ret