#include "prodConsProblem.h"
#include "stdLib.h"
#include "shell.h"

int sharedInt=0;

void prodConsDemo()
{
  semStart(SEM_MUTEX_KEY,1);
  semStart(SEM_OVERFLOW_KEY,1);
  semStart(SEM_UNDERFLOW_KEY,0);
  int exitFlag=0;
  char input=0;
  sysPrintString(" 1. Producer\n 2. Consumer\n 3. Exit\n",CB,CG,CR);
  while(!exitFlag)
  {
    sysGetChar(&input);
    if(input== '1')
    {
      sysPrintString("Generated a Producer!\n",CB,CG,CR);
      sysExecute(producer, "Producer");
    }
    else if(input=='2')
    {
      sysPrintString("Generated a Consumer!\n",CB,CG,CR);
      sysExecute(consumer, "Consumer");
    }
    else if(input=='3')
    {
      exitFlag=1;
    }
    else
    {
      if(input!=0)
      {
        sysPrintString("Wrong input!\n",CB,CG,CR);
      }
    }
  }
  semStop(SEM_MUTEX_KEY);
  semStop(SEM_OVERFLOW_KEY);
  semStop(SEM_UNDERFLOW_KEY);
}

void producer()
{
  semWait(SEM_OVERFLOW_KEY);
  semWait(SEM_MUTEX_KEY);
  sharedInt++;
  sysPrintInt(sharedInt,DB,DG,DR);
  semSignal(SEM_UNDERFLOW_KEY);
  semSignal(SEM_MUTEX_KEY);
}

void consumer()
{
  semWait(SEM_UNDERFLOW_KEY);
  semWait(SEM_MUTEX_KEY);
  sysPrintInt(sharedInt,DB,DG,DR);
  sharedInt--;
  semSignal(SEM_OVERFLOW_KEY);
  semSignal(SEM_MUTEX_KEY);
}
