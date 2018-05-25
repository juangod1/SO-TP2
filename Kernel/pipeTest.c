#include "pipeTest.h"


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

void given100Writes()
{
  char c = 'z';
  for(int i=0; i<100; i++)
  {
    write(&global_pipe, c);
  }
}

void given99Reads()
{
  char c;
  for(int i=0; i<99; i++)
  {
    read(&global_pipe, &c);
  }
}

void whenReading()
{
  char c;
  read(&global_pipe, &c);
}

void thenReadIndexIsZero()
{
  if(global_pipe->readIndex==0)
  {
    ok();
  }
  else
  {
    fail("Expected read one, found another number\n");
  }
}

void thenCountIsOne()
{
 if(global_pipe->count==0)
  {
    ok();
  }
  else
  {
    fail("Expected count one, found another number\n");
  }
}

void pipeTestMain()
{
  printString("Entering pipe test\n",TB,TG,TR);
  printString("Testing initialization\n",TB,TG,TR);
  givenANonInitializedPipe();
  whenInitializingPipe();
  thenSuccess();

  printString("Testing circularity of write\n",TB,TG,TR);
  givenAnInitializedPipe();
  whenAdding101elements();
  thenReadIndexIsOne();
  thenWriteIndexIsOne();
  thenCountIsOneHundred();

  printString("Testing circularity of read\n",TB,TG,TR);
  givenAnInitializedPipe();
  given100Writes();
  given99Reads();
  whenReading();
  thenReadIndexIsZero();
  thenCountIsOne();

  givenANonInitializedPipe();

}
