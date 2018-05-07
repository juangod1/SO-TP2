#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <sys/types.h>
#include "scheduler.h"

#define HEAP_START 0x400000
#define HEAP_END 0x799999
#define NUM_OF_PAGES ((HEAP_END - HEAP_START)/PAGE_SIZE)
#define PAGE_SIZE 0x4000


typedef struct bookBlockStruct * bookBlock;
struct bookBlockStruct {
	int owner; //Este es el  pid
	void* base;
	int brk; //Este puede ser otro tipo de dato para ahorrar memoria
	bookBlock next;
};

typedef struct dataBlockStruct * dataBlock;
struct dataBlockStruct {
	size_t size;
	dataBlock next;
	int free;
};

#define DBLOCK_SIZE (sizeof(struct dataBlockStruct))
#define BBLOCK_SIZE (sizeof(struct bookBlockStruct))

//Memory manager handling functions
int initMemoryManager();
void initPageDirArray();
void* mm_malloc(size_t s);
void mm_free();
void * popNewPage();
void dropPage(int id);
bookBlock searchBookedBlock(int id);

//Public functions
void * malloc(size_t size);
void free(void *pointer);

//Internal page functions
dataBlock getDataBlock(void *pointer);
dataBlock getLastDataBlock(dataBlock first);
dataBlock searchFreeBlock(dataBlock last, size_t size);

//N2H
void *mymalloc(size_t size);
dataBlock expandHeap(dataBlock* last, size_t size);
void *sbrk(size_t s);

#endif
