//
// Created by francisco on 17/05/18.
//

#include "include/MemoryDriver.h"
#include "hashMap.h"
#include "lib.h"
#include "include/videoDriver.h"

blockID lastBlock = 0;

// maps blockID to address
map_t blockTable;

int writeBlock(blockID id, void * data)
{
    return hashmapPut(blockTable,intToString(id),data);
}


// returns blockID;
blockID createBlock()
{
    int address = malloc(BLOCK_SIZE);
    lastBlock++;
    char * lb = intToString(lastBlock);
    hashmapPut(blockTable, lb, address);
    printString("Creating block with id, address: \n",238,130,238);
    printString(lb,238,130,238);
    printString(", ",238,130,238);
    printInt(address,238,130,238);
    printString("\n",238,130,238);
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

void mdTester(){
    initializeMemoryDriver();
    createBlock();
    printString("TEST MD\n",255,255,255);
    //hashmapIterate(blockTable,printWrap,0);
    int * b;
    readBlock(b,1);
    printInt(*b,255,0,0);
}

void printWrap(int dummy, void * data){
    printString("Entry: ",255,255,255);
    printInt(data, 255,255,255);
    printString("\n",255,255,255);
}
