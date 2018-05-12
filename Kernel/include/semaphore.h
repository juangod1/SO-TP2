#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "semaphoreProcessQueue.h"
#include "lib.h"
#include "memorymanager.h"
#include "semaphoreProcessQueue.h"
#include "scheduler.h"

typedef struct semStruct * semaphore;
struct semStruct
{
	int value;
	queueEntry processQueue;
};

void semaphoreInitialization(semaphore * sem, int value);
int taskRequest(semaphore sem, int pid);
void taskFinished(semaphore sem, int pid);
void semaphoreFinalization(semaphore * sem);
void exit();

#endif
