#include "videoDriver.h"
#include "exceptions.h"
#include "stdlib.h"
#include <stdint.h>
#define ZERO_EXCEPTION_ID 0
#define OVERFLOW_EXCEPTION_ID 4
#define INVALID_OPCODE_EXCEPTION_ID 6

static char* registers[] = {"RAX: ", " RBX: ", " RCX: ", " RDX: ", " RBP: ", "RDI: ", " RSI: ", " R8: "
					, " R9: ", " R10: ", "R11: ", " R12: ", " R13: ", " R14: ", " R15: ", " RIP: "};

void zero_division(uint64_t* rsp);
void overflow(uint64_t* rsp);
void opcode(uint64_t* rsp);
void printRegs(uint64_t*rsp);

void exceptionDispatcher(uint64_t exception, uint64_t* rsp) {

	switch(exception){
		case ZERO_EXCEPTION_ID:
			zero_division(rsp);
			break;
		case OVERFLOW_EXCEPTION_ID:
			overflow(rsp);
			break;
		case INVALID_OPCODE_EXCEPTION_ID:
			opcode(rsp);
			break;
	}
}

void zero_division(uint64_t* rsp) {
	printString("Error: division by zero\n",0,155,255);
	printRegs(rsp);
	//while(1); //Return to shell

}

void overflow(uint64_t* rsp){
	printString("Error: overflow\n",0,155,255);
	printRegs(rsp);
	//while(1);
}

void opcode(uint64_t* rsp){
	printString("Error: invalid opcode exception\n",0,155,255);
	printRegs(rsp);
	//while(1);
}

void printRegs(uint64_t*rsp){
	for(int i = 0 ; i < 16 ; i++){
		if(i%5==0){
			printString("\n",0,155,255);
		}
		printString(registers[i],0,155,255);
		printHex(rsp[i]);
	}
	printString("\n",0,155,255);

}
