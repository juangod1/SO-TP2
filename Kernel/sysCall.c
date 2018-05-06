#include "interrupts.h"
#include "videoDriver.h"
#include "time.h"
#include "keyboardDriver.h"
#include "schedulerTest.h"
#include "include/schedulerTest.h"
#include "include/IPCTester.h"
#include "scheduler.h"
#include "include/semaphoreList.h"
#include "include/messaging.h"

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
                IPCTester();
                schedulerTestRun();
                break;
	        case 1:
	            schedulerTestRun();
	            break;
	        case 2:
	            IPCTester();
       	        break;
	    }
	    break;
    case 7:
      printString("Entered kernel side syscall\n",0,0,0);
      execute((void *)rsi, (char*)rdx);
      break;
    case 8:
      getPid((pid_t*)rsi);
      break;
    case 9:
      listProcesses(rsi, rdx);
      break;
    case 10:
      sendMessage((mbd_t)rsi, (void *)rdx);
      break;
    case 11:
      recieveMessage((mbd_t)rsi, (void *)rdx);
      break;
    case 12:
      finalizeMessageBox((mbd_t)rsi);
      break;
    case 13:
      wait((int)rsi);
      break;
    case 14:
      signal((int)rsi);
      break;
    case 15:
      startSemaphore((int)rsi,rdx);
      break;
    case 16:
      stopSemaphore((int)rsi);
      break;
  }
}
