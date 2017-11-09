#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"
#include "naiveConsole.h"
#include "keyboardDriver.h"

void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
  switch(rdi){
    case 3:
      getTimeRTC(rsi);
      break;
    case 4:
      getChar((char *)rsi);
      break;
    case 6:
      clearScreen();
      break;
    case 7:
      writeChar((char)rsi,rdx,rcx,r8);
      break;
    case 8:
      paintPixel(rsi, rdx, (char)rcx, (char)r8, (char)r9);
      break;
  }
}
