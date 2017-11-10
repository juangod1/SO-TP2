#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION_ID 4
#define INVALID_OPCODE_EXCEPTION_ID 6
#define GENERAL_PROTECTION_EXCEPTION_ID 13

void exceptionDispatcher(uint64_t exception, uint64_t* rsp);
void zero_division(uint64_t* rsp);
void overflow(uint64_t* rsp);
void opcode(uint64_t* rsp);
void generalProtection(uint64_t* rsp);
void printRegs(uint64_t*rsp);

static char* registers[] = {"RAX: ", " RBX: ", " RCX: ", " RDX: ", " RBP: ", "RDI: ", " RSI: ", " R8: "
					, " R9: ", " R10: ", "R11: ", " R12: ", " R13: ", " R14: ", " R15: ", " RIP: "};

#endif
