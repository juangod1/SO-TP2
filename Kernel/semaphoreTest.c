#include <stdlib.h>
#include <stdio.h>
#include "include/testLib.h"
#include "include/semaphore.h"
#include "include/processQueue.h"
#include "include/semaphoreTest.h"


semaphore global_semaphore;
int global_pid;

void givenAnEmptySemaphore()
{
  global_semaphore=NULL;
}

void static givenAPid()
{
  global_pid=1;
}

void givenAnInitializedSemaphore()
{
  semaphoreInitialization(&global_semaphore);
}

void whenSemaphoreIsInitialized()
{
  semaphoreInitialization(&global_semaphore);
}

void whenSemaphoreIsFinalized()
{
  semaphoreFinalization(&global_semaphore);
}

void thenSemaphoreIsNoLongerNull()
{
  if(global_semaphore!=NULL)
  {
    ok();
  }
  else
  {
    fail("Expected non null pointer, found null pointer\n");
  }
}

void thenSemaphoreIsNull()
{
    if(global_semaphore==NULL)
    {
      ok();
    }
    else
    {
      fail("Expected null pointer, found non null pointer\n");
    }
}

void whenRequestingATask()
{
  taskRequest(global_semaphore, global_pid);
}

void thenProcessQueueIsEmpty()
{
  if(processQueueSize(&(global_semaphore->processQueue))==0)
  {
    ok();
  }
  else
  {
    fail("Expected to find empty process queue, found not empty process queue\n");
  }
}

void thenSemaphoreValueIsZero()
{
  if(global_semaphore->value==0)
  {
    ok();
  }
  else
  {
    fail("Expected to find semaphore value zero, found non zero semaphore value\n");
  }
}

void givenAPreviousTaskRequest()
{
  taskRequest(global_semaphore, global_pid);
}

void thenProcessQueueHasOneElement()
{
    if(processQueueSize(&(global_semaphore->processQueue))==1)
    {
      ok();
    }
    else
    {
      fail("Expected process queue of size 1, found process queue of different size\n");
    }
}

void thenSemaphoreValueIsMinusOne()
{
  if(global_semaphore->value==-1)
  {
    ok();
  }
  else
  {
    fail("Expected to find semaphore value -1, found different value\n");
  }
}

void semaphoreInitializationTest()
{
  givenAnEmptySemaphore();
  whenSemaphoreIsInitialized();
  thenSemaphoreIsNoLongerNull();
}

void semaphoreFinalizationTest()
{
  givenAnInitializedSemaphore();
  whenSemaphoreIsFinalized();
  thenSemaphoreIsNull();
}

void taskRequestTest()
{
  givenAPid();
  givenAnInitializedSemaphore();
  whenRequestingATask();
  thenProcessQueueIsEmpty();
  thenSemaphoreValueIsZero();
}

void twoTasksRequestTest()
{
  givenAPid();
  givenAnInitializedSemaphore();
  givenAPreviousTaskRequest();
  whenRequestingATask();
  thenProcessQueueHasOneElement();
  thenSemaphoreValueIsMinusOne();
}

void static setConditionsBackToNormal()
{
  semaphoreFinalization(&global_semaphore);
}

void semaphoreTestMain()
{
  //printString("Testing semaphore initialization\n",0,0,255);
  semaphoreInitializationTest();
	setConditionsBackToNormal();
  //printString("Testing semaphore finalization\n",0,0,255);
  semaphoreFinalizationTest();
	setConditionsBackToNormal();
  //printString("Testing task request\n",0,0,255);
  taskRequestTest();
	setConditionsBackToNormal();
  //printString("Testing double task request\n",0,0,255);
  twoTasksRequestTest();
	setConditionsBackToNormal();
}
