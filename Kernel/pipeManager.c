#include "pipeManager.h"


pipeManagerPTR pipeManager=NULL;

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

pipeNode * findPipeNode(input)
{
  return recursiveFindPipeNode(&(pipeManager->first),input);
}

pipeNode * recursiveFindPipeNode(pipeNode * pn, int input)
{
  if(pn==NULL || (*pn)==NULL)
  {
    return NULL;
  }
  if((*pn)->index==input)
  {
    return pn;
  }
  return recursiveFindPipeNode(&((*pn)->next),input);
}

void readFromPipe(int input,char * c)
{
  pipeNode * pn=findPipeNode(input);
  if(pn==NULL)
  {
    return;
  }
  read(&((*pn)->p), c);
}

void writeToPipe(int output, char c)
{
  pipeNode * pn=findPipeNode(output);
  if(pn==NULL)
  {
    return;
  }
  write(&((*pn)->p), c);
}


void finalizePipeManager()
{
  if(pipeManager ==NULL)
  {
    return;
  }
  recursiveFinalizePipeNode(&(pipeManager->first));
  free(pipeManager);
  pipeManager=NULL;
}

void initializePipeManager()
{
  finalizePipeManager();
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


void addRecursivePipeNode(pipeNode * pn, int index_P)
{
  if(pn==NULL || (*pn)==NULL)
  {
    (*pn)=malloc(sizeof(struct pipeNode_CDT));
    (*pn)->next=NULL;
    (*pn)->index=index_P;
    initializePipe(&((*pn)->p));
    return;
  }
  if((*pn)->index==index_P)
  {
    return;
  }
  return addRecursivePipeNode(&((*pn)->next), index_P);
}

void addPipeNode(int index)
{
  return addRecursivePipeNode(&(pipeManager->first),index);
}

void removeRecursivePipeNode(pipeNode * pn, int index_P)
{
  if(pn==NULL || (*pn)==NULL)
  {
    return;
  }
  if((*pn)->index==index_P)
  {
    pipeNode aux=(*pn)->next;
    finalizePipeNode(pn);
    (*pn)=aux;
    return;
  }
  return removeRecursivePipeNode(&((*pn)->next), index_P);
}

void removePipeNode(int index)
{
  return removeRecursivePipeNode(&(pipeManager->first), index);
}

int recursivePipeManagerSize(pipeNode * pn)
{
  if(pn==NULL || (*pn)==NULL)
  {
    return 0;
  }
  return 1 + recursivePipeManagerSize(&((*pn)->next));
}

int pipeManagerSize()
{
  return recursivePipeManagerSize(&(pipeManager->first));
}
