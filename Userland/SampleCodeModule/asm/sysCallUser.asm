section .text

GLOBAL sysCall

sysCall:
  push rbp
  mov rbp,rsp
  push rbx

  ; C rdi,rsi,rdx,rcx
  ; syscalls rax,rbx,rcx,rdx
  mov rax, rdi
  mov rbx, rsi
  mov r10, rcx ; switch rdx rcx
  mov rcx, rdx
  mov rdx, r10

  int 80h

  pop rbx
  mov rsp,rbp
  pop rbp
  ret
