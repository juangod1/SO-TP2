#include "prodConsProblem.h"
#include "stdLib.h"


int sharedInt=0;

void prodConsDemo(int value)
{
  semStart(SEM_MUTEX_KEY,1);
  semStart(SEM_OVERFLOW_KEY,value);
  semStart(SEM_UNDERFLOW_KEY,0);
  int exitFlag=0; char input=0;
  char str[2];
  sysPrintString(" 1. Producer\n 2. Consumer\n 3. Exit\n",255,255,0);
  while(!exitFlag)
  {
    sysGetChar(&input);
    str[0]=input;
    str[1]=0;
    sysPrintString(str,255,255,2);
    switch(input)
    {
      case '1':
        sysPrintString("Generated a Producer!\n",255,255,0);
        sysExecute(producer, "Producer");
      break;
      case '2':
        sysPrintString("Generated a Consumer!\n",255,255,0);
        sysExecute(consumer, "Consumer");
      break;
      case '3':
        exitFlag=1;
      break;
      case 0:
      break;
      default:
        sysPrintString("Wrong input!\n",255,255,0);
      break;
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
  sysPrintInt(sharedInt, 255,255,0);
  semSignal(SEM_UNDERFLOW_KEY);
  semSignal(SEM_MUTEX_KEY);
}

void consumer()
{
  semWait(SEM_UNDERFLOW_KEY);
  semWait(SEM_MUTEX_KEY);
  sysPrintInt(sharedInt, 255,255,0);
  sharedInt--;
  semSignal(SEM_OVERFLOW_KEY);
  semSignal(SEM_MUTEX_KEY);
}
