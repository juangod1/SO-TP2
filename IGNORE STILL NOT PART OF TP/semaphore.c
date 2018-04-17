#include <stdlib.h>
#include <stdio.h>
#include "semaphore.h"
#include "processQueue.h"


void semaphoreInitialization(semaphore * sem)
{
  (*sem) = malloc(sizeof(struct semStruct));
  (*sem)->value=1;
  (*sem)->processQueue=NULL;
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
