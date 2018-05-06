#include "include/semaphoreProcessQueueTest.h"
#include "include/semaphoreListTest.h"
#include "include/semaphoreTest.h"
#include "include/messagingTest.h"
#include "include/videoDriver.h"
#include "include/lib.h"
#include "include/testLib.h"

int IPCTester()
{
  printString("Testing Semaphore List\n",TB,TG,TR);
  semaphoreListTestMain();
  printString("Testing Semaphore Process Queue\n",TB,TG,TR);
  processQueueTestMain();
  printString("Testing Semaphore\n",TB,TG,TR);
  semaphoreTestMain();
  printString("Testing Messaging\n",TB,TG,TR);
  messagingTestMain();
  return 0;
}
