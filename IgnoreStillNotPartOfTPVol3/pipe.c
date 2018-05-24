#include <stdio.h>
#include <stdlib.h>
#include "testlib.h"

#define PIPESIZE 100

typedef struct pipe_CDT * pipe;
struct pipe_CDT {
    char readIndex;
    char writeIndex;
    char count;
    char * buffer;
};

int isEmpty(pipe * p)
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
  if(isEmpty(p))
  {

  }
  else
  {
    *c=(*p)->buffer[(*p)->readIndex];
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
  (*p)->buffer[(*p)->writeIndex]=c;
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

pipe global_pipe;

void givenANonInitializedPipe()
{
  finalizePipe(&global_pipe);
}
void whenInitializingPipe()
{
  initializePipe(&global_pipe);
}

void givenAnInitializedPipe()
{
  finalizePipe(&global_pipe);
  initializePipe(&global_pipe);
}

void whenAdding101elements()
{
  char c = 'z';
  for(int i=0; i<101; i++)
  {
    write(&global_pipe, c);
  }
}

void thenReadIndexIsOne()
{
  if(global_pipe->readIndex==1)
  {
    ok();
  }
  else
  {
    fail("Expected readIndex one, found another number\n");
  }
}

void thenWriteIndexIsOne()
{
  if(global_pipe->writeIndex==1)
  {
    ok();
  }
  else
  {
    fail("Expected writeIndex one, found another number\n");
  }
}

void thenCountIsOneHundred()
{
  if(global_pipe->count==100)
  {
    ok();
  }
  else
  {
    fail("Expected count equal to one, found another number\n");
  }
}

int main()
{
  givenANonInitializedPipe();
  whenInitializingPipe();
  thenSuccess();

  givenAnInitializedPipe();
  whenAdding101elements();
  thenReadIndexIsOne();
  thenWriteIndexIsOne();
  thenCountIsOneHundred();

}
