#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "processQueue.h"

typedef struct semStruct * semaphore;
struct semStruct
{
	int value;
	queueEntry processQueue;
};

void semaphoreInitialization(semaphore * sem);
int taskRequest(semaphore sem, int pid);
void taskFinished(semaphore sem, int pid);
void semaphoreFinalization(semaphore * sem);

#endif
