#ifndef SEMAPHORELIST_H
#define SEMAPHORELIST_H

#include "semaphoreProcessQueue.h"
#include "semaphore.h"


typedef struct listEntryStruct * listEntry;
struct listEntryStruct
{
	int key;
	semaphore sem;
	listEntry next;
};


typedef struct trafficControl_Struct * trafficControlPTR;
struct trafficControl_Struct
{
	listEntry semaphoreList;
};


int listContains(int key, listEntry * me_P);
int listSize(listEntry * me_P);
int createlistEntry(int key_P, int value_P, listEntry * me_P);
int removelistEntry(listEntry * me_P);
int removeListEntryByKey(int key_P, listEntry * me_P);
void totalListRemove(listEntry * me_P);


listEntry * getListEntry(int key_P, listEntry * lE);


void wait(int key_P);
void signal(int key_P);
void startSemaphore(int key, int value);
void stopSemaphore(int key_P);


void initializeTrafficControl();

#endif
