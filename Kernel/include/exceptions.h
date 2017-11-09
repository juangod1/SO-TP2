#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

void exceptionDispatcher(int exception, uint64_t* rsp);
void zero_division(uint64_t* rsp);
void overflow(uint64_t* rsp);
void opcode(uint64_t* rsp);
//void printRegs(uint64_t*rsp);

#endif
