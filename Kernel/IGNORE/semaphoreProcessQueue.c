#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "semaphoreProcessQueue.h"

int processQueueSize(queueEntry *q)
{
  if((*q)==NULL)
  {
    return 0;
  }
  return 1 + processQueueSize(&((*q)->next));
}

void processQueueAdd(int pid_P,queueEntry * q)
{
  if((*q)==NULL)
  {
    (*q)=malloc(sizeof(struct queueEntryStruct));
    (*q)->pid=pid_P;
    (*q)->next=NULL;
  }
  else
  {
    processQueueAdd(pid_P, &((*q)->next));
  }
}

int processQueueRemove(queueEntry * q)
{
  if((*q)==NULL){
    return -1;
  }
  queueEntry aux = (*q)->next;
  int ret =(*q)->pid;
  free((*q));
  (*q)=aux;
  return ret;
}

void totalQueueRemove(queueEntry * q)
{
	if((*q)==NULL)
	{
			return;
	}
	if((*q)!=NULL)
	{
		 totalQueueRemove(&((*q)->next));
	}
	free((*q));
	(*q)=NULL;
	return;
}
