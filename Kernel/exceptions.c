#include "exceptions.h"

#define EB 0
#define EG 155
#define ER 255

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
	printString("Error: division by zero\n",EB,EG,ER);
	printRegs(rsp);
}

void overflow(uint64_t* rsp){
	printString("Error: overflow\n",EB,EG,ER);
	printRegs(rsp);
}

void opcode(uint64_t* rsp){
	printString("Error: invalid opcode exception\n",EB,EG,ER);
	printRegs(rsp);
}

void generalProtection(uint64_t* rsp){
	printString("Error: general protection exception\n",EB,EG,ER);
	printRegs(rsp);
}

void printRegs(uint64_t*rsp){
	for(int i = 0 ; i < 16 ; i++){
		if(i%5==0){
			printString("\n",EB,EG,ER);
		}
		printString(registers[i],EB,EG,ER);
		printHex(rsp[i],EB,EG,ER);
	}
	printString("\n",EB,EG,ER);
}
