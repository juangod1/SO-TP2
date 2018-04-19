#include <stdlib.h>
#include <stdio.h>
#include "testlib.h"
#include "semaphore.h"
#include "processQueue.h"


void semaphoreInitialization(semaphore * sem)
{
  (*sem) = malloc(sizeof(struct semStruct));
  (*sem)->value=1;
  (*sem)->processQueue=NULL;
  return;
}

void semaphoreFinalization(semaphore * sem)
{
  if((*sem)==NULL)
  {
    return;
  }
  int pid;
  while(processQueueSize(&((*sem)->processQueue))>0)
  {
    pid=processQueueRemove(&((*sem)->processQueue));
    //schedulerResume(pid);
  }
  totalQueueRemove(&((*sem)->processQueue));
  free((*sem));
  (*sem)=NULL;
  return;
}

int taskRequest(semaphore sem, int pid) //eventually will have to ask pid type
{
  sem->value--;
  if(sem->value >=0)
  {
    return 0;
  }
  //schedulerWait(pid)
  processQueueAdd(pid, &(sem->processQueue));
}

void taskFinished(semaphore sem, int pid) //eventually will have to ask for pid type
{
  sem->value++;
  if(sem->value <1)
  {
    int newProcess=processQueueRemove(&(sem->processQueue));
    //schedulerResume(pid)
  }
}