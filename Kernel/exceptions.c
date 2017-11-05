#include "naiveConsole.h"
#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION_ID 4
#define INVALID_OPCODE_EXCEPTION_ID 6

void zero_division();

void exceptionDispatcher(int exception,uint64_t rip) {
	ncPrint("                                                         ");

	if (exception == ZERO_EXCEPTION_ID)
		zero_division(rip);
}

void zero_division(uint64_t rip) {
	ncPrint("Error: division by zero ");
	ncPrintHex(rip);
}
