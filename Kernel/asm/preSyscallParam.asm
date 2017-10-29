section .text

GLOBAL preSyscallParam
extern sysCallHandler

preSyscallParam:
; C rdi,rsi,rdx,rcx
; syscalls rax,rbx,rcx,rdx
  push rbp
  mov rbp,rsp
  push rbx

  mov rdi, rax
  mov rsi, rbx
  mov r10, rdx ; switch rdx rcx
  mov rdx, rcx
  mov rcx, r10

  pop rbx
  mov rsp,rbp
  pop rbp

  call sysCallHandler
  ret
