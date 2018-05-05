#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"
#include "keyboardDriver.h"
#include "schedulerTest.h"
#include "scheduler.h"

void sysCallHandler(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9){
  switch(rdi){
    case 1:
      getTimeRTC(rsi);
      break;
    case 2:
      getChar((char *)rsi);
      break;
    case 3:
      clearScreen();
      break;
    case 4:
      writeChar((char)rsi,rdx,rcx,r8);
      break;
    case 5:
      paintPixel(rsi, rdx, (char)rcx, (char)r8, (char)r9);
      break;
    case 6:
        switch(rsi){
            case 0:
                mainTester();
                schedulerTestRun();
                break;
	        case 1:
	            schedulerTestRun();
	            break;
	        case 2:
	            mainTester();
       	        break;
	    }
	    break;
    case 7:
      printString("Entered kernel side syscall\n",0,0,0);
      execute(rsi);
      break;

    case 8:
      getPid((pid_t*)rsi);
      break;

  }
}
