#ifndef SO_TP2_FILESYSTEM_H
#define SO_TP2_FILESYSTEM_H

#define MAX_FILENAME 20

#include "MemoryDriver.h"
#include "hashMap.h"

typedef struct file_CDT * file;

struct file_CDT
{
    int isFile;
    int isOpen;
    char fileName [MAX_FILENAME];
    blockID startingBlock;
};

void initializeFS();
void f_open(char* name, char* path);
void f_close(char* name, char* path);
void f_read(char* name, char* path, int offset, int bytes);
void f_write(char* name, char* path, int offset, void * data, int dataSize);
void f_mkdir(char* name, char* path);
void f_chdir(char* name);
void f_create(char* name, char * path);
map_t parseDirectory(char * path);

#endif SO_TP2_FILESYSTEM_H