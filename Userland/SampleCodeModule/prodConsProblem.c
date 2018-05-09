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
  sysPrintString("Producer arrived\n",255,0,255);
  semWait(SEM_OVERFLOW_KEY);
  sysPrintString("Producer passed overflow\n", 255, 0, 255);
  semWait(SEM_MUTEX_KEY);
  sysPrintString("Producer passed mutex\n", 255, 0, 255);
  sysPrintString("LEMO",255,255,0);
  sharedInt++;
  sysPrintString("LEMO", 255, 255, 0);
  sysPrintInt(sharedInt,DB,DG,DR);
  sysPrintString("Producer sending signals\n", 255, 0, 255);
  semSignal(SEM_MUTEX_KEY);
  sysPrintString("Producer sent mutex\n", 255, 0, 255);
  semSignal(SEM_UNDERFLOW_KEY);
  sysPrintString("Producer sent underflow\n", 255, 0, 255);
  sysExit();
}

void consumer()
{
  sysPrintString("consumer arrived\n", 255, 0, 255);
  semWait(SEM_UNDERFLOW_KEY);
  sysPrintString("consumer passed overflow\n", 255, 0, 255);
  semWait(SEM_MUTEX_KEY);
  sysPrintString("consumer passed mutex\n", 255, 0, 255);
  sysPrintInt(sharedInt,DB,DG,DR);
  sysPrintString("consumer sending signals\n", 255, 0, 255);
  sharedInt--;
  sysPrintString("about to send signal\n",255,0,255);
  semSignal(SEM_MUTEX_KEY);
  sysPrintString("consumer sent mutex\n", 255, 0, 255);
  semSignal(SEM_OVERFLOW_KEY);
  sysPrintString("consumer sent underflow\n", 255, 0, 255);
  sysExit();
}
