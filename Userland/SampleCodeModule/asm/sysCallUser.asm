
GLOBAL sysCall
section .text

sysCall:
  push rbp
  mov rbp,rsp

  ; C arguments by rdi,rsi,rdx,rcx
  int 80h

  mov rsp,rbp
  pop rbp
  ret
