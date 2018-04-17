#include <stdlib.h>
#include <stdio.h>
#include "semaphoreList.h"

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
		(*me_P) = malloc(sizeof(listEntry));
		(*me_P)->key=key_P;
		(*me_P)->next=NULL;

		(*me_P)->sem=malloc(sizeof(semaphore));
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

int removelistEntry(int key_P, listEntry * me_P)
{
	if((*me_P) == NULL)
	{
		return -1;
	}
	if((*me_P)->key==key_P)
	{
		free((*me_P)->sem->processQueue);
		free((*me_P)->sem);
		free((*me_P));
		(*me_P)=NULL;
		return 0;
	}
	if((*me_P)->next == NULL)
	{
		return -1;
	}
	if((*me_P)->next->key==key_P)
	{
		listEntry aux = (*me_P)->next->next;
		free((*me_P)->next->sem->processQueue);
		free((*me_P)->next->sem);
		free((*me_P)->next);
		(*me_P)->next=aux;
		return 0;
	}
	return removelistEntry(key_P, &((*me_P)->next));
}