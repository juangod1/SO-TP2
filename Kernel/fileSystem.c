//
// Created by francisco on 17/05/18.
//

#include "include/fileSystem.h"
#include "include/hashMap.h"
#include "include/MemoryDriver.h"
#include <stdint.h>
#include "videoDriver.h"
#include <stddef.h>

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
    hashmapGet(table, name, fileBuffer);

    file f = fileBuffer[0];
    if(f==NULL){
        f_create(name,path);
        f_open(name,path);
    }
    else{
        f->isOpen = 1;
    }
}

void f_close(char* name, char* path)
{
    map_t table = parseDirectory(path);
    file fileBuffer[1];
    hashmapGet(table, name, fileBuffer);

    file f = fileBuffer[0];
    if(f==NULL){
        return;
    }
    else{
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

map_t parseDirectoryRecursive(char * path, map_t prevTable){
    printString(path,244,0,244);
    char buffer[MAX_FILENAME];
    char count=1;

    while(path[count] != '\0' && path[count] != '/' && count<=MAX_FILENAME+1){
        buffer[count-1] = path[count];
        count++;
    }
    buffer[count]='\0';
    printString(buffer,244,244,0);
    file temp;
    hashmapGet(prevTable, buffer, &temp);

    if(temp == NULL || count>MAX_FILENAME+1)
        return;

    map_t map;
    hashmapGet(fileAllocationTable,temp->fileName,&map);

    if(path[count]=='\0')
        return map;

    return parseDirectoryRecursive(path+count,map);
}

map_t parseDirectory(char * path){
    if(strcmp(path,"/")==0){
        return rootDirectoryTable;
    }

    return parseDirectoryRecursive(path, rootDirectoryTable);
}

int filenameExists(char * name, map_t directoryTable){
    file b[1];
    hashmapGet(directoryTable,name,b);
    return (b[0]==NULL)?0:1;
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