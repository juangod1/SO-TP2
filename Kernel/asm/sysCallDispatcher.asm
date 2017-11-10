GLOBAL sysCallDispatcher
extern sysCallHandler

section .text

%include "./asm/macros.m"

sysCallDispatcher:
  pushStateNoRax
  call sysCallHandler
  popStateNoRax
  iretq
