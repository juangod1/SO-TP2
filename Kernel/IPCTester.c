#include "include/semaphoreProcessQueueTest.h"
#include "include/semaphoreListTest.h"
#include "include/semaphoreTest.h"
#include "include/messagingTest.h"
#include "include/videoDriver.h"
#include "include/lib.h"

int IPCTester()
{
  printString("Testing Semaphore List\n",0,255,255);
  semaphoreListTestMain();
  printString("Testing Semaphore Process Queue\n",0,255,255);
  processQueueTestMain();
  printString("Testing Semaphore\n",0,255,255);
  semaphoreTestMain();
  printString("Testing Messaging\n",0,255,255);
  messagingTestMain();
  return 0;
}
