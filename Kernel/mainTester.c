#include <stdio.h>
#include "include/semaphoreProcessQueueTest.h"
#include "include/semaphoreListTest.h"
#include "include/semaphoreTest.h"
#include "include/messagingTest.h"

int mainTester()
{
  printString("\n________________________________\n\n...Commencing semaphoreListTest...\n\n________________________________\n\n",0,0,255);
  semaphoreListTestMain();
  printString("\n________________________________\n\n...Commencing ProcessQueueTest...\n\n________________________________\n\n",0,0,255);
  processQueueTestMain();
  printString("\n________________________________\n\n...Commencing semaphoreTest...\n\n________________________________\n\n",0,0,255);
  semaphoreTestMain();
  printString("\n________________________________\n\n...Commencing messagingTest...\n\n________________________________\n\n",0,0,255);
  messagingTestMain();
  return 0;
}
