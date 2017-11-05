#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"
#include "naiveConsole.h"
#include "keyboardDriver.h"

void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
  switch(rdi){
    case 1:
      printString(rsi,rdx,r8,r9);
      break;
    case 2:
      printInt(rsi,rdx,r8,r9);
      break;
    case 3:
      getTimeRTC(rsi);
      break;
    case 4: ;
        getChar(rsi);
      break;
    case 5:
      readInput((char *)rsi);
      break;
    case 6:
      ncClear();
      break;
    case 7:
      writeChar(*((char*)rsi),color_red,color_green,color_blue);
      break;
  }
}
