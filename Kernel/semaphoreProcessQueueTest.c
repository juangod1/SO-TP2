#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "include/testLib.h"
#include "include/semaphoreProcessQueue.h"

queueEntry globalTestingQueue;
int globalPid;
int comparativeGlobalPid;


void givenAnEmptyQueue()
{
  globalTestingQueue==NULL;
}

void whenRemovingAnElement()
{
  globalPid=processQueueRemove(&globalTestingQueue);
}

void thenElementRemovedIsMinusOne()
{
  if(globalPid==-1)
  {
    ok();
  }
  else
  {
    fail("Expected pid value -1, found some other number\n");
  }
}

void thenSemaphoreQueueIsEmpty()
{
  if(globalTestingQueue==NULL)
  {
    ok();
  }
  else
  {
    fail("Expected null value, found non null value\n");
  }
}





void givenAChangeInValue()
{
  globalPid=2;
}

void static givenAPid()
{
  globalPid=1;
}

void whenAddingAnElement()
{
  processQueueAdd(globalPid, &globalTestingQueue);
}

void thenElementIsAdded()
{
  if(processQueueSize(&globalTestingQueue)==1)
  {
    ok();
    processQueueRemove(&globalTestingQueue);
  }
  else
  {
    fail("Expected size equal to 1, found size different to 1\n");
  }
}

void givenAnAddition()
{
  processQueueAdd(globalPid, &globalTestingQueue);
}
void thenElementRemovedIsEqual()
{
  if(globalPid==1)
  {
    ok();
  }
  else
  {
    fail("Expected to find equal integers, found different integers\n");
  }
}

void testCantRemoveWhenEmpty()
{
  givenAnEmptyQueue();
  whenRemovingAnElement();
  thenElementRemovedIsMinusOne();
  thenQueueIsEmpty();
}

void testQueueAddition()
{
  givenAPid();
  givenAnEmptyQueue();
  whenAddingAnElement();
  thenElementIsAdded();
}

void testQueueRemoval()
{
  givenAPid();
  givenAnEmptyQueue();
  givenAnAddition();
  givenAChangeInValue();
  whenRemovingAnElement();
  thenElementRemovedIsEqual();
  thenQueueIsEmpty();
}

void givenADifferentPid()
{
  comparativeGlobalPid=2;
}

void givenADifferentAddition()
{
  processQueueAdd(comparativeGlobalPid, &globalTestingQueue);
}

void thenElementIsEqualToFirst()
{
  if(globalPid==1)
  {
    ok();
  }
  else
  {
    fail("Expected to find pid equal to one, found pid not equal to one\n");
  }
}

void thenQueueSizeIsOne()
{
  if(processQueueSize(&globalTestingQueue)==1)
  {
    ok();
    processQueueRemove(&globalTestingQueue);
  }
  else
  {
    fail("Expected to find process queue size equal to one, found process queue size not equal to one\n");
  }
}

void testThatRemoveRemovesFirst()
{
  givenAPid();
  givenADifferentPid();
  givenAnEmptyQueue();
  givenAnAddition();
  givenADifferentAddition();
  whenRemovingAnElement();
  thenElementIsEqualToFirst();
  thenQueueSizeIsOne();
}

void setConditionsBackToNormal()
{
  totalQueueRemove(&globalTestingQueue);
}


void processQueueTestMain()
{
  printString("Testing queue addition\n",0,255,255);
  testQueueAddition();
  setConditionsBackToNormal();
  printString("Testing queue removal\n",0,0,255);
  testQueueRemoval();
  setConditionsBackToNormal();
  printString("Testing removal order\n",0,0,255);
  testThatRemoveRemovesFirst();
  setConditionsBackToNormal();
  printString("Testing removal when empty\n",0,0,255);
  testCantRemoveWhenEmpty();
  setConditionsBackToNormal();
}
