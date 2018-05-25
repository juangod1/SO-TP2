#include "pipe.h"

int isPipeEmpty(pipe * p)
{
  if(p==NULL||(*p)==NULL || (*p)->count==0){
    return 1;
  }
  return 0;
}

void initializePipe(pipe * p)
{
  (*p)=malloc(sizeof(struct pipe_CDT));
  (*p)->readIndex=0;
  (*p)->writeIndex=0;
  (*p)->count=0;
  (*p)->buffer=malloc(PIPESIZE);
}

void finalizePipe(pipe * p)
{
  if(p==NULL || *p==NULL)
  {
    return;
  }
  free((*p)->buffer);
  (*p)->buffer=NULL;
  free((*p));
  (*p)=NULL;
}

void read(pipe * p, char * c)
{
  if(p==NULL || *p==NULL)
  {
    return;
  }
  if(isPipeEmpty(p))
  {

  }
  else
  {
    *c=(*p)->buffer[(int)(*p)->readIndex];
    (*p)->readIndex=((*p)->readIndex+1)%PIPESIZE;
    (*p)->count--;
  }
}

void write(pipe * p, char c)
{
  if(p==NULL || *p==NULL)
  {
    return;
  }
  (*p)->buffer[(int)(*p)->writeIndex]=c;
  (*p)->writeIndex= ((*p)->writeIndex+1)%PIPESIZE;
  if((*p)->count==PIPESIZE)
  {
    (*p)->readIndex++;
  }
  else
  {
    (*p)->count++;
  }
}
