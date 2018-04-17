#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct semStruct * semaphore;
struct semStruct
{
	int value;
	int * processQueue; //eventually will have to be pid type
};

void semaphoreInitialization(semaphore * sem);
int taskRequest(semaphore sem, int pid);
void taskFinished(semaphore sem, int pid);

#endif
