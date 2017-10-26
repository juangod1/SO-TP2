GLOBAL sysCall

section .text

sysCall:
  push rbp
  mov rbp,rsp
  ; SWITCH CON TODAS LAS FUNCIONES DE sysCall
  mov rsp,rbp
  pop rbp
  iret
