#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <sys/types.h>
#include "scheduler.h"
#include "videoDriver.h"
#include "testLib.h"

#define HEAP_START 0x400000
#define HEAP_END 0x799999
#define NUM_OF_PAGES ((HEAP_END - HEAP_START)/PAGE_SIZE)
#define NUM_OF_BBLOCKS (PAGE_SIZE/BBLOCK_SIZE)
#define PAGE_SIZE 0xF000


typedef struct bookBlockStruct * bookBlock;
struct bookBlockStruct {
	int owner; //Este es el  pid+2
	void* base;
	void* stack;
	int brk;
	bookBlock prev;
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
void initMemoryManagerBlocksArray();
void* mm_malloc(size_t s);
void mm_free(void* pointer);
void * malloc(size_t size);
void free(void *pointer);

//Internal page functions
dataBlock getDataBlock(void *pointer);
dataBlock getLastDataBlock(dataBlock first);
dataBlock searchFreeBlock(dataBlock last, size_t size);
bookBlock searchBookedBlock(int id);
void * popNewPage();
void * popReverseNewPage();
void dropBookPageForProcess(int pid);
void dropPage(uint64_t dir);
void mmShow();
void pbShow();

//Public functions
void expandHeap(dataBlock * db, size_t s);
void getMyHeapBase(dataBlock * db);
void* getStack(int pid);

#endif
