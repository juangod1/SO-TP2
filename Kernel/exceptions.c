#include "stdlib.h"
#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION_ID 4
#define INVALID_OPCODE_EXCEPTION_ID 6

void zero_division();

void exceptionDispatcher(int exception) {

	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
}

void zero_division() {

	printString("Error: division by zero\n",0,0,0);
	while(1);
}
