#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"

void sysCallHandler(int edi, int esi, int edx, int ecx){
  switch(edi){
    case 1:
      printString(esi,edx);
      break;
    case 2:
      printInt(esi,edx);
      break;
    case 3:
      getTimeRTC(esi);
      break;
  }
}
