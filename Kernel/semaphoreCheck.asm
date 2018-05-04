section .txt
BITS 64

GLOBAL semaphoreCheck

semaphoreCheck:
  push rbp
  mov rbp, rsp

  mov eax, 1
  mov ecx, 0
  lock cmpxchg [rdi], ecx
  je FAIL

  mov eax, 0
  jmp END
FAIL:
  mov eax, 1
END:
  mov rsp, rbp
  pop rbp
  ret
