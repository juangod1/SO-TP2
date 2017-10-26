section .text

GLOBAL key_pressed
GLOBAL get_key

key_pressed:
  push rbp
  mov rbp, rsp
  
  in al, 64h
  and al, 1h

  mov rsp, rbp
  pop rbp
  ret

get_key:
  push rbp
  mov rbp, rsp

  and rax, 0h
  in al, 60h

  mov rsp, rbp
  pop rbp
  ret
