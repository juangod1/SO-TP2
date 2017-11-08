#include "videoDriver.h"

#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION_ID 4
#define INVALID_OPCODE_EXCEPTION_ID 6

void zero_division();
extern printRegs();
void exceptionDispatcher(int exception) {

	switch(exception){
		case ZERO_EXCEPTION_ID:
			zero_division();
			break;
		case OVERFLOW_EXCEPTION_ID:
			overflow();
			break;
		case INVALID_OPCODE_EXCEPTION_ID:
			opcode();
			break;
	}
}

void zero_division() {
	printString("Error: division by zero\n",0,155,255);
	printRegs();
	//while(1); //Return to shell
	
}

void overflow(){
	printString("Error: overflow\n",0,155,255);
	printRegs();
	while(1);
}

void opcode(){
	printString("Error: invalid opcode exception\n",0,155,255);
	printRegs();
	while(1);
}