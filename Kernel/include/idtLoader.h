#ifndef IDTLOADER_H_
#define IDTLOADER_H_

#include <stdint.h>

void load_idt();
void preSyscallParam(int rdi, int rsi, int rdx, int rcx);

#endif
