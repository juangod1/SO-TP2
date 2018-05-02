#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BLOCK_SIZE sizeof(dataBlockStruct)
#define HEAP_START = 0x10100000
#define HEAP_END = 0x10200000

typedef struct bookBlockStruct * bookBlock;
struct bookBlockStruct {
	int owner; //Este es el  pid 
	void* base;
	int brk; //Este puede ser otro tipo de dato para ahorrar memoria
	struct bookBlockStruct* next;
}bookBlockStruct;

typedef struct dataBlockStruct * dataBlock;
struct dataBlockStruct {
	size_t size;
	struct dataBlockStruct* next;
	int free;
}dataBlockStruct;


#endif