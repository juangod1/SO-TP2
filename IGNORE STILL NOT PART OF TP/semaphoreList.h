#ifndef SEMAPHORELIST_H
#define SEMAPHORELIST_H

#include "processQueue.h"
#include "semaphore.h"

typedef struct listEntryStruct * listEntry;
struct listEntryStruct
{
	int key;
	semaphore sem;
	listEntry next;
};


int listContains(int key, listEntry * me_P);
int listSize(listEntry * me_P);
int createlistEntry(int key_P, listEntry * me_P);
int removelistEntry(listEntry * me_P);
int removeListEntryByKey(int key_P, listEntry * me_P);
void totalListRemove(listEntry * me_P);


#endif
