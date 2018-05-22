//
// Created by francisco on 17/05/18.
//

#include "include/MemoryDriver.h"
#include "hashMap.h"
#include "lib.h"

blockID lastBlock = 0;

// maps blockID to address
map_t blockTable;

int writeBlock(blockID id, void * data)
{
    return hashmapPut(blockTable,intToString(id),data);
}


// returns blockID;
void createBlock()
{
    int address = malloc(BLOCK_SIZE);
    lastBlock++;
    hashmapPut(blockTable,lastBlock,intToString(lastBlock));
    return lastBlock;
}

// puts data address in pointer value
// pointer -----> address -----> block data
int readBlock(void * pointer, blockID id)
{
    return hashmapGet(blockTable,intToString(id),pointer);
}

int deleteBlock(blockID id)
{
    return hashmapRemove(blockTable, intToString(id));
}

void initializeMemoryDriver(){
    blockTable = newHashMap();
}

