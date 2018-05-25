#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include "memorymanager.h"

typedef struct queueEntryStruct * queueEntry;
struct queueEntryStruct
{
	int pid;// pid_t
	queueEntry next;
};

int processQueueSize(queueEntry *q);
void processQueueAdd(int pid_P,queueEntry * q);
int processQueueRemove(queueEntry * q); //EVENTUALLY HAVE TO CHANGE RETURN TO PID_T
void totalQueueRemove(queueEntry * q);

#endif
