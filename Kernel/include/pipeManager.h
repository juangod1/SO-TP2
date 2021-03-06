#ifndef PIPEMANAGER_H
#define PIPEMANAGER_H

#include "pipe.h"
#include "memorymanager.h"
#include "lib.h"

typedef struct pipeNode_CDT * pipeNode;
struct pipeNode_CDT {
  pipe p;
  int index;
  pipeNode next;
};

typedef struct pipeManager_CDT * pipeManagerPTR;
struct pipeManager_CDT {
  pipeNode first;
};


void finalizePipeNode(pipeNode * pn);
void recursiveFinalizePipeNode(pipeNode * pn);
void finalizePipeManager();
void initializePipeManager();
void initializePipeNode(pipeNode * pn);
void addRecursivePipeNode(pipeNode * pn, int index_P);
void addPipeNode(int index);
void removeRecursivePipeNode(pipeNode * pn, int index_P);
void removePipeNode(int index);
int recursivePipeManagerSize(pipeNode * pn);
int pipeManagerSize();
pipeNode * recursiveFindPipeNode(pipeNode * pn, int input);
pipeNode * findPipeNode(input);
void readFromPipe(int input,char * c);
void writeToPipe(int output, char c);

#endif
