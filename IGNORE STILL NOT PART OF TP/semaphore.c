#include "semaphore.h"
#include "processQueue.h"

void semaphoreInitialization(semaphore * sem)
{
  (*sem) = malloc(sizeof(semStruct));
  (*sem)->value=1;
  return;
}

int taskRequest(semaphore sem, int pid) //eventually will have to ask pid type
{
  value--
  if(sem->value >=0)
  {
    return 0;
  }
  //schedulerWait(pid)
  processQueuePush(pid, &(sem->processQueue));
}

void taskFinished(semaphore sem, int pid) //eventually will have to ask for pid type
{
  value++
  if(sem->value <1)
  {
    int newProcess=processQueuePop(&(sem->processQueue));
    //schedulerResume(pid)
  }
}
