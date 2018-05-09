#include "include/semaphore.h"
#include "include/lib.h"
#include "include/memorymanager.h"
#include "include/semaphoreProcessQueue.h"
#include "include/scheduler.h"

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
    printString("SemaphoreCheck returns true!\n",0,255,0);
    return 0;
  }
    printString("SemaphoreCheck returns false!\n",0,0,255);
  sem->value--;
  printString("Pid: ",0,255,0);
  printInt(pid,0,255,0);
  printString("\n",0,0,0);
  processQueueAdd(pid, &(sem->processQueue));
  printString("before sleep, PID: \n",30,60,90);
  printInt(pid,30,60,90);
  sleepProcess(pid);
  printString("After sleep.\n",255,255,255);
  return 0;
}

void taskFinished(semaphore sem, int pid) //eventually will have to ask for pid type
{
  sem->value++;
  printString("Sem value in task finished:",255,0,255);
  printInt(sem->value,255,0,255);
  printString("\n", 255, 0, 255);
  if(sem->value <1)
  {
    pid_t newProcess=processQueueRemove(&(sem->processQueue));
    wakeProcess(newProcess);
  }
}
