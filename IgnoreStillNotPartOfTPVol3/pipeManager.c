#include "pipe.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct pipeNode_CDT * pipeNode;
struct pipeNode_CDT {
  pipe p;
  pipeNode next;
};

typedef struct pipeManager_CDT * pipeManagerPTR;
struct pipeManager_CDT {
  pipeNode first;
};

pipeManagerPTR pipeManager;

void initializePipeManager()
{
  pipeManager=malloc(sizeof(struct pipeManager_CDT));
  pipeManager->first=NULL;
}

void initializePipeNode(pipeNode * pn)
{
  if(pn==NULL || (*pn)==NULL)
  {
    return;
  }
  (*pn)=malloc(sizeof(struct pipeNode_CDT));
  initializePipe(&((*pn)->p));
  (*pn)->next=NULL;
}

void finalizePipeNode(pipeNode * pn)
{
  if(pn==NULL || (*pn)==NULL)
  {
    return;
  }
  finalizePipe(&((*pn)->p));
  free(*pn);
  (*pn)=NULL;
}

void recursiveFinalizePipeNode(pipeNode * pn)
{
  if(pn==NULL || (*pn)==NULL)
  {
    return;
  }
  recursiveFinalizePipeNode(&((*pn)->next));
  finalizePipeNode(pn);
}

void finalizePipeManager()
{
  recursiveFinalizePipeNode(&(pipeManager->first));
  free(pipeManager);
}


/*
int main()
{

}
*/
