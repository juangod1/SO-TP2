//
// Created by francisco on 17/05/18.
//

#ifndef SO_TP2_MEMORYDRIVER_H
#define SO_TP2_MEMORYDRIVER_H

#include <stdint.h>

#define BLOCK_SIZE 256

typedef uint64_t blockID;


int writeBlock(blockID id, void * data);
blockID createBlock();
int readBlock(void * pointer, blockID id);
int deleteBlock(blockID id);
void initializeMemoryDriver();
void mdTester();
void printWrap(int dummy, void * data);

#endif //SO_TP2_MEMORYDRIVER_H
