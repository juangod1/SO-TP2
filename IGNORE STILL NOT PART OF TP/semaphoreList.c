#include <stdlib.h>
#include <stdio.h>
#include "semaphoreList.h"
#include "processQueue.h"
#include "semaphore.h"


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

int createlistEntry(int key_P, listEntry * me_P)
{
	if((*me_P)==NULL)
	{
		(*me_P) = malloc(sizeof(struct listEntryStruct));
		(*me_P)->key=key_P;
		(*me_P)->next=NULL;

		(*me_P)->sem=malloc(sizeof(struct semStruct));
		(*me_P)->sem->value=1;
		(*me_P)->sem->processQueue=NULL;
		return 0;
	}
	if((*me_P)->key==key_P)
	{
		return 1;
	}
	return createlistEntry(key_P, &((*me_P)->next));
}

int removeListEntryByKey(int key_P, listEntry * me_P)
{
	if((*me_P)==NULL)
	{
		return 1;
	}
	if((*me_P)->key==key_P)
	{
		removelistEntry(me_P);
	}
	removeListEntryByKey(key_P, &((*me_P)->next));
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
		totalQueueRemove(&((*me_P)->sem->processQueue));
		free((*me_P)->sem->processQueue);
		free((*me_P)->sem);
	}
	free(*me_P);
	(*me_P)=aux;
	return 0;

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
