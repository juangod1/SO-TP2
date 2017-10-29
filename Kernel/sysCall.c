#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"



void sysCallHandler(int rdi, int rsi, int rdx, int rcx){

  printInt(2,rdi);
  printString(2,"-");
  printInt(2,rsi);
  printString(2,"-");
  printInt(2,rdx);
  printString(2,"-");
  printInt(2,rcx);
  printString(2,"-");
  newLine();
  switch(rdi){
    case 1:
      printString(rsi,rdx);
      break;
    case 2:
      printInt(rsi,rdx);
      break;
    case 3:
      getTimeRTC(rsi);
      break;
    case 4:
      newLine();
      break;
    case 5:
      readInput(rsi);
      break;
  }
}
