//
// Created by francisco on 17/05/18.
//

#include "include/fileSystem.h"
#include "include/hashMap.h"
#include "include/MemoryDriver.h"
#include <stdint.h>

// maps filename to file { isFile, isOpen, fileName, startingBlock}
map_t rootDirectoryTable;

// maps blockID to char[2] {busy, next}
map_t fileAllocationTable;


void initializeFS()
{
    rootDirectoryTable = newHashMap();
    fileAllocationTable = newHashMap();
    initializeMemoryDriver();
}

void f_open(char* name, char* path)
{
    map_t table = parseDirectory(path);
    file fileBuffer[1];
    hashmapGet(table, name, f);

    if(f==NULL){
        f_create(name,path);
        f_open(name,path);
    }
    else{
        file f = fileBuffer[0];
        f->isOpen = 1;
    }
}

void f_close(char* name, char* path)
{
    map_t table = parseDirectory(path);
    file fileBuffer[1];
    hashmapGet(table, name, f);

    if(f==NULL){
        return;
    }
    else{
        file f = fileBuffer[0];
        f->isOpen = 0;
    }
}


// TODO
void f_read(char* name, char* path, int offset, int bytes)
{

}

//TODO
void f_write(char* name, char* path, int offset, void * data, int dataSize)
{

}

//TODO
map_t parseDirectory(char * path){
    return (char*)0;
}

//TODO
int filenameExists(char * name, map_t directoryTable){
    return 0;
}

// A directory is a block which contains a pointer to a directory table (map_t)
void f_mkdir(char* name, char* path)
{
    map_t dir = parseDirectory(path);

    if(filenameExists(name,dir))
        return;

    blockID id = createBlock();

    file newFile = malloc(sizeof(struct file_CDT));
    newFile->isFile = 0;
    newFile->isOpen = 0;
    memcpy(newFile->fileName, name);
    newFile->startingBlock= id;

    hashmapPut(dir, name, newFile);

    map_t newDirectoryTable = newHashMap();
    writeBlock(id, newDirectoryTable);

    // write FAT entry
    char * entry = malloc(2);
    entry[0]=0; //busy
    entry[1]=-1; //next
    hashmapPut(fileAllocationTable,id,entry);

}

void f_create(char * name, char * path){
    map_t dir = parseDirectory(path);

    if(filenameExists(name,dir))
        return;

    blockID id = createBlock();

    file newFile = malloc(sizeof(struct file_CDT));
    newFile->isFile = 1;
    newFile->isOpen = 0;
    memcpy(newFile->fileName, name);
    newFile->startingBlock= id;

    hashmapPut(dir, name, newFile);


    // write FAT entry
    char * entry = malloc(2);
    entry[0]=0; //busy
    entry[1]=-1; //next
    hashmapPut(fileAllocationTable,id,entry);
}