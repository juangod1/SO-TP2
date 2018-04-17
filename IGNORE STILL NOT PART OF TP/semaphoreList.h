#ifndef SEMAPHORELIST_H
#define SEMAPHORELIST_H


typedef struct semStruct * semaphore;
struct semStruct
{
	int value;
	int * processQueue;
};

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
int removelistEntry(int key_P, listEntry * me_P);


#endif