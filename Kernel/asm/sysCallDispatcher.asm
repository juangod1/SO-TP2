section .text

GLOBAL sysCallDispatcher
extern sysCallHandler

sysCallDispatcher:
  push rbp
  mov rbp, rsp

  call sysCallHandler

  mov rsp, rbp
  pop rbp
  iretq
