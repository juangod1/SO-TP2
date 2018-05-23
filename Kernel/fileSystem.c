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
    file fileBuffer;
    hashmapGet(table, name, &fileBuffer);

    file f = fileBuffer;
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
    file fileBuffer;
    hashmapGet(table, name, &fileBuffer);

    file f = fileBuffer;
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

map_t parseDirectoryRecursive(char * path, map_t prevTable)
{
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
    printString("got obj ",244,244,0);printInt(temp,244,244,0);
    if(temp == NULL || count>MAX_FILENAME+1)
        return NULL;

    map_t b;
    readBlock(&b, temp->startingBlock);
    printString("got map ",244,244,0);printInt(b,244,244,0);

    if(path[count]=='\0'){
        printString("Returning ",100,0,100);
        printString(temp->fileName,100,0,100);
        printString(" -- address: ",100,0,100);
        printInt(b,100,0,100);
        return b;
    }


    return parseDirectoryRecursive(path+count+1,b);
}

map_t parseDirectory(char * path){
    printString("Parsing ",34,70,130);
    printString(path,34,70,130);
    if(strcmp(path,"/")==0){
        printString("Returning root /",100,0,100);
        return rootDirectoryTable;
    }

    return parseDirectoryRecursive(path, rootDirectoryTable);
}

int filenameExists(char * name, map_t directoryTable){
    file b;
    hashmapGet(directoryTable,name,&b);
    printString(name,34,70,130);
    printString(" filename exists: ",34,70,130);
    printInt((b==NULL)?0:1,34,70,130);
    return (b==NULL)?0:1;
}

// A directory is a block which contains a pointer to a directory table (map_t)
void f_mkdir(char* name, char* path)
{
    if(strleng(name)>MAX_FILENAME){
        return;
    }

    map_t dir = parseDirectory(path);
    printString("Parsed dir address: ",34,70,130);
    printInt(dir,0,100,0);
    if(filenameExists(name,dir)){
        return;
    }

    blockID id = createBlock();

    file newFile = malloc(sizeof(struct file_CDT));

    newFile->isFile = 0;
    newFile->isOpen = 0;
    memcpy(newFile->fileName, name, strleng(name));
    newFile->fileName[strleng(name)+1]='\0';
    newFile->startingBlock= id;
    printString("Putting filename in DIR:",34,70,130);
    printString(newFile->fileName,34,70,130);
    printInt(newFile,34,70,130);
    hashmapPut(dir, newFile->fileName, newFile);
    map_t newDirectoryTable = newHashMap();
    printString("      writing in block ",255,255,255);
    printInt(id ,255,255,255);
    printString(" data ",255,255,255);
    printInt(newDirectoryTable,255,255,255);
    writeBlock(id, newDirectoryTable, sizeof(map_t));

    // write FAT entry
    char * entry = malloc(2);
    entry[0]=0; //busy
    entry[1]=-1; //next
    hashmapPut(fileAllocationTable,intToString(id),entry);

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