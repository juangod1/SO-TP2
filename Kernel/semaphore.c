#include "include/semaphore.h"

extern int semaphoreCheck(void * ptr);

void semaphoreInitialization(semaphore * sem, int value)
{
  int realValue = (value<=0)?0:1;
  (*sem) = malloc(sizeof(struct semStruct));
  (*sem)->value=realValue;
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
    wakeProcess(pid);
  }
  totalQueueRemove(&((*sem)->processQueue));
  free((*sem));
  (*sem)=NULL;
  return;
}

int taskRequest(semaphore sem, int pid) //eventually will have to ask pid type
{
  if(semaphoreCheck(&(sem->value)))
  {
    return 0;
  }
  sem->value--;
  processQueueAdd(pid, &(sem->processQueue));
  sleepProcess(pid);
  return 0;
}

void taskFinished(semaphore sem, int pid) //eventually will have to ask for pid type
{
  sem->value++;
  if(sem->value <1)
  {
    pid_t newProcess=processQueueRemove(&(sem->processQueue));
    wakeProcess(newProcess);
  }
}
