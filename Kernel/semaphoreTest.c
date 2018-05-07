#include "include/testLib.h"
#include "include/semaphore.h"
#include "include/processQueue.h"
#include "include/videoDriver.h"
#include "include/semaphoreTest.h"
#include "include/lib.h"


semaphore global_semaphore;
int global_pid;
int global_semaphore_value=1;

void givenAnEmptySemaphore()
{
  global_semaphore=NULL;
}

void givenAPRocessPid()
{
  global_pid=1;
}

void givenAnInitializedSemaphore()
{
  semaphoreInitialization(&global_semaphore,global_semaphore_value);
}

void whenSemaphoreIsInitialized()
{
  semaphoreInitialization(&global_semaphore,global_semaphore_value);
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
  givenAPRocessPid();
  givenAnInitializedSemaphore();
  whenRequestingATask();
  thenProcessQueueIsEmpty();
  thenSemaphoreValueIsZero();
}

void twoTasksRequestTest()
{
  givenAPRocessPid();
  givenAnInitializedSemaphore();
  givenAPreviousTaskRequest();
  whenRequestingATask();
  thenProcessQueueHasOneElement();
  thenSemaphoreValueIsMinusOne();
}

void setSemaphoreConditionsBackToNormal()
{
  semaphoreFinalization(&global_semaphore);
}

void semaphoreTestMain()
{
  printString("Testing semaphore initialization\n",0,0,255);
  semaphoreInitializationTest();
	setSemaphoreConditionsBackToNormal();
  printString("Testing semaphore finalization\n",0,0,255);
  semaphoreFinalizationTest();
	setSemaphoreConditionsBackToNormal();
  printString("Testing task request\n",0,0,255);
  taskRequestTest();
	setSemaphoreConditionsBackToNormal();
  printString("Testing double task request\n",0,0,255);
  twoTasksRequestTest();
	setSemaphoreConditionsBackToNormal();
}
