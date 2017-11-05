#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"
#include "naiveConsole.h"


void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
  /*printString(2,"syscall params received: ");
  printInt(2,rdi);
  printString(2,"-");
  printInt(2,rsi);
  printString(2,"-");
  printInt(2,rdx);
  printString(2,"-");
  printInt(2,rcx);
  newLine();*/
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
    case 4:
      newLine();
      break;
    case 5:
      readInput((char *)rsi);
      break;
    case 6:
      ncClear();
    case 7:
      plotFunction(rsi,rdx,rcx);
  }
}
