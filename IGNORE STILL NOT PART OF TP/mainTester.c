#include <stdio.h>
#include "processQueueTest.h"
#include "semaphoreListTest.h"
#include "semaphoreTest.h"

int main()
{
  printf("\n________________________________\n\n...Commencing semaphoreListTest...\n\n________________________________\n\n");
  semaphoreListTestMain();
  printf("\n________________________________\n\n...Commencing ProcessQueueTest...\n\n________________________________\n\n");
  processQueueTestMain();
  printf("\n________________________________\n\n...Commencing semaphoreTest...\n\n________________________________\n\n");
  semaphoreTestMain();
}
