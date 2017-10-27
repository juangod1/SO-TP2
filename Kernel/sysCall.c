#include "interrupts.h"
#include "videoDriver.h"

void sysCallHandler(int edi, int esi, int edx, int ecx){
  switch(edi){
    case 1:
      printString(esi,(const char*)edx);
      break;
  }
}
