//
// Created by francisco on 17/05/18.
//

#include "include/MemoryDriver.h"
#include "hashMap.h"
#include "lib.h"
#include "include/videoDriver.h"
#include "fileSystem.h"

blockID lastBlock = 0;

// maps blockID to address
map_t blockTable;

int writeBlock(blockID id, void * data, int bytes)
{

    printString("TAB AD: ",0,130,0);
    printInt(blockTable,0,130,0);
    any_t block=10;
    char * sid = intToString(id);
    int ret = hashmapGet(blockTable,sid,&block);
    printString("writing in ",0,0,255);
    printInt(block,0,0,255);

    memcpy(block,&data,bytes);
    return ret;
}


// returns blockID;
blockID createBlock()
{
    int address = malloc(BLOCK_SIZE);
    lastBlock++;
    char * lb = intToString(lastBlock);
    printString("Creating block with id, address: \n",238,130,238);
    printString(lb,238,130,238);
    printString(", ",238,130,238);
    printInt(address,238,130,238);
    printString("\n",238,130,238);
    printString("TAB AD: ",0,130,0);
    printInt(blockTable,0,130,0);
    int r = hashmapPut(blockTable, lb, address);
    printString("ret is : ",0,130,45);
    printInt(r,0,130,45);
    any_t a;
    hashmapGet(blockTable, lb, &a);
    printString("a is: ",255,255,255);
    printInt(a,255,255,255);
    return lastBlock;
}

// puts data address in pointer value
// pointer -----> address -----> block data
int readBlock(void * pointer, blockID id)
{
    printString("readblock\n",2,255,255);
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
    initializeFS();
    f_mkdir("bin","/");
    f_mkdir("bash","/bin");
    printString("TEST MD\n",255,255,255);

    parseDirectory("/bin/bash");
}

void printWrap(int dummy, void * data){
    printString("Entry: ",255,255,255);
    printInt(data, 255,255,255);
    printString("\n",255,255,255);
}
