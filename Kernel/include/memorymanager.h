#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define HEAP_START 0x400000
#define HEAP_END 0x799999
#define NUM_OF_PAGES ((HEAP_END - HEAP_START)/PAGE_SIZE)
#define PAGE_SIZE 0x1000

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

void initPageDirArray();
void * malloc(size_t size);
void free(void *pointer);

#define BLOCK_SIZE (sizeof(struct dataBlockStruct))

#endif