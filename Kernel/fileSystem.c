//
// Created by francisco on 17/05/18.
//

#include "include/fileSystem.h"
#include "include/hashMap.h"


// maps filename to starting block
map_t rootDirectoryTable;
// maps block to <busy, next>
map_t fileAllocationTable;


void initializeFS()
{
    rootDirectoryTable = newHashMap();
    fileAllocationTable = newHashMap();
}

void f_open(char* path, int mode)
{
    file fd = hashmapGet(rootDirectoryTable, path, fd) ;

    if(fd == (char*)0)
    {
        f_create(fd, path, mode);
    }




}

void f_close()
{

}

void f_read(file f)
{

}

void f_seek(file f)
{

}

void f_mkdir(char* name)
{

}

void f_chdir(char* name)
{
    
}

void f_create(file fd, char * path, int mode){

}