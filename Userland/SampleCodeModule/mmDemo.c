#include "mmDemo.h"
#include "stdLib.h"
#include "shell.h"


void mmDemo()
{
  sysPrintString("Amount of bytes to malloc: ", CB,CG,CR);

  int exitFlag=1;
  char input=0;

  char * nombre = sysMalloc(5);
  nombre = "joaco";
  sysPrintString("\nTu nombre es: ", CB,CG,CR);
  sysPrintString(nombre, CB,CG,CR);
  sysPrintString("\n", CB,CG,CR);
/*  while(!exitFlag)
  {
    sysGetChar(&input);
    if(input > '0' && input < '9')
    {
      sysPrintString("Generated a Producer!\n",CB,CG,CR);
      sysExecute(producer, "Producer");
    }
    else if(input=='2')
    {
      sysPrintString("Generated a Consumer!\n",CB,CG,CR);
      sysExecute(consumer, "Consumer");
    }
    else if(input'3')
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
  }*/
}

/*void producer()
{
  semWait(SEM_OVERFLOW_KEY);
  semWait(SEM_MUTEX_KEY);
  sharedInt++;
  sysPrintInt(sharedInt,DB,DG,DR);
  semSignal(SEM_UNDERFLOW_KEY);
  semSignal(SEM_MUTEX_KEY);
  sysExit();
}

void consumer()
{
  semWait(SEM_UNDERFLOW_KEY);
  semWait(SEM_MUTEX_KEY);
  sysPrintInt(sharedInt,DB,DG,DR);
  sharedInt--;
  semSignal(SEM_OVERFLOW_KEY);
  semSignal(SEM_MUTEX_KEY);
  sysExit();
}
*/
