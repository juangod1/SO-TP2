#include "include/semaphoreList.h"
#include "include/semaphoreProcessQueue.h"
#include "include/semaphore.h"
#include "include/scheduler.h"
#include "include/memorymanager.h"

trafficControlPTR trafficControl;

void initializeTrafficControl()
{
	trafficControl=malloc(sizeof(struct trafficControl_Struct));
	trafficControl->semaphoreList=NULL;
}

void finalizeTrafficControl()
{
	totalListRemove(&(trafficControl->semaphoreList));
	free(trafficControl);
}


int listContains(int key, listEntry * me_P)
{
	if((*me_P)==NULL)
	{
		return 0;
	}
	if((*me_P)->key==key)
	{
		return 1;
	}
	return listContains(key, &((*me_P)->next));
}

int listSize(listEntry * me_P)
{
	if((*me_P)==NULL)
	{
		return 0;
	}
	return 1 + listSize(&((*me_P)->next));
}

int createlistEntry(int key_P, int value_P, listEntry * me_P)
{
	if((*me_P)==NULL)
	{
		(*me_P) = malloc(sizeof(struct listEntryStruct));
		(*me_P)->key=key_P;
		(*me_P)->next=NULL;

		(*me_P)->sem=malloc(sizeof(struct semStruct));
		(*me_P)->sem->value=value_P;
		(*me_P)->sem->processQueue=NULL;
		return 0;
	}
	if((*me_P)->key==key_P)
	{
		return 1;
	}
	return createlistEntry(key_P, value_P,&((*me_P)->next));
}

int removeListEntryByKey(int key_P, listEntry * me_P)
{
	if((*me_P)==NULL)
	{
		return 1;
	}
	if((*me_P)->key==key_P)
	{
		return removelistEntry(me_P);
	}
	return removeListEntryByKey(key_P, &((*me_P)->next));
}

int removelistEntry(listEntry * me_P)
{
	if(*(me_P)==NULL)
	{
		return 0;
	}
	listEntry aux=(*me_P)->next;
	if((*me_P)->sem!=NULL)
	{
		semaphoreFinalization(&((*me_P)->sem));
	}
	free(*me_P);
	(*me_P)=aux;
	return 0;
}

listEntry * getListEntry(int key_P, listEntry * lE)
{
	if(lE==NULL || *lE ==NULL)
	{
		return NULL;
	}
	if((*lE)->key==key_P)
	{
		return lE;
	}
	return getListEntry(key_P, &((*lE)->next));
}

void wait(int key_P)
{
	listEntry * lE=getListEntry(key_P, &(trafficControl->semaphoreList));
	if(lE!=NULL && (*lE)!=NULL)
	{
		taskRequest((*lE)->sem, getPid());
	}
}

void signal(int key_P)
{
	listEntry * lE=getListEntry(key_P, &(trafficControl->semaphoreList));
	if(lE!=NULL && (*lE)!=NULL)
	{
		taskFinished((*lE)->sem, getPid());
	}
}

void stopSemaphore(int key_P)
{
	removeListEntryByKey(key_P, &(trafficControl->semaphoreList));
}

void startSemaphore(int key, int value)
{
	createlistEntry(key,value,&(trafficControl->semaphoreList));
}

void totalListRemove(listEntry * me_P)
{
	if((*me_P)==NULL)
	{
			return;
	}
	if((*me_P)!=NULL)
	{
		 totalListRemove(&((*me_P)->next));
	}
	removelistEntry(me_P);
	return;
}
