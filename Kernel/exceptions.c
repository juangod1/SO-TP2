#include "videoDriver.h"
#include "exceptions.h"
#include "stdlib.h"
#include <stdint.h>

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
		case GENERAL_PROTECTION_EXCEPTION_ID:
			generalProtection(rsp);
	}
}

void zero_division(uint64_t* rsp) {
	printString("Error: division by zero\n",0,155,255);
	printRegs(rsp);
}

void overflow(uint64_t* rsp){
	printString("Error: overflow\n",0,155,255);
	printRegs(rsp);
}

void opcode(uint64_t* rsp){
	printString("Error: invalid opcode exception\n",0,155,255);
	printRegs(rsp);
}

void generalProtection(uint64_t* rsp){
	printString("Error: general protection exception\n",0,155,255);
	printRegs(rsp);
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
