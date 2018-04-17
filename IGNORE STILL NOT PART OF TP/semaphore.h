#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "processQueue.h"

typedef struct semStruct * semaphore;
struct semStruct
{
	int value; //eventually will have to be pid type
	queueEntry processQueue;
};

void semaphoreInitialization(semaphore * sem);
int taskRequest(semaphore sem, int pid);
void taskFinished(semaphore sem, int pid);
void semaphoreFinalization(semaphore * sem);

#endif
