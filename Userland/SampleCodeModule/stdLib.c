#include "stdLib.h"
#include <stdint.h>

extern int sysCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

void sysPrintString(char * string, int R, int G, int B){
  sysCall(1,string,R,G,B,0);
}

void sysPrintInt(int num, int R, int G, int B){
  sysCall(2,num,R,G,B,0);
}
void sysGetChar(char * ch){
  sysCall(4,ch,0,0,0,0);
}
void sysReadInput(char * buffer){
  sysCall(5,buffer,0,0,0,0);
}
void sysWriteChar(char * ch){
  sysCall(7,ch,0,0,0,0);
}


void sysGetTime(int * buffer){
	buffer[0] = sysCall(3,0,0,0,0,0); // Seconds
	buffer[1] = sysCall(3,2,0,0,0,0); // Minutes
	buffer[2] = sysCall(3,4,0,0,0,0); // Hours
	buffer[3] = sysCall(3,7,0,0,0,0); // Day
	buffer[4] = sysCall(3,8,0,0,0,0); // Month
	buffer[5] = sysCall(3,9,0,0,0,0); // Year
}

void sysClear(){
	sysCall(6,2,0,0,0,0);
}
