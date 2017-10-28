#include "stdLib.h"
#include <stdint.h>

extern void sysCall(int edi, int esi, int edx, int ecx);

void sysPrintString(uint8_t color, char * string){
  sysCall(1,color,string,0);
}

void sysPrintInt(uint8_t color, int num){
  sysCall(2,color,num,0);
}

void sysGetTime(int * buffer){
  sysCall(3,buffer,0,0);
}
