#include "pipeManagerTest.h"



void givenAnInitializedPipeManager()
{
  initializePipeManager();
}

void whenAdding10ElementsWithSameIndex()
{
  int index=10;
  for(int i=0; i<10; i++)
  {
    addPipeNode(index);
  }
}

void thenPipeManagerSizeIsOne()
{
  if(pipeManagerSize()==1)
  {
    ok();
  }
  else
  {
    fail("Expected pipe manager size equal to one, found another number\n");
  }
}

void whenAdding10ElementsWithDifferentIndex()
{
  for(int i=0; i<10; i++)
  {
    addPipeNode(i);
  }
}

void thenPipeManagerSizeIsTen()
{
  if(pipeManagerSize()==10)
  {
    ok();
  }
  else
  {
    fail("Expected pipe manager size equal to ten, found another number\n");
  }
}

void given10AdditionsWithDifferentIndex()
{
  for(int i=0; i<10; i++)
  {
    addPipeNode(i);
  }
}

void whenRemovingAnElementFromPipeManager()
{
  int index=7;
  removePipeNode(index);
}

void thenPipeManagerSizeIsNine()
{
  if(pipeManagerSize()==9)
  {
    ok();
  }
  else
  {
    fail("Expected pipe manager size equal to nine, found another number\n");
  }
}

void whenRemovingANonExistingElement()
{
  int index=10001;
  removePipeNode(index);
}

void pipeManagerTestMain()
{
  printString("Entering pipeManager test\n",TB,TG,TR);
  printString("Testing multiple same additions\n",TB,TG,TR);
  givenAnInitializedPipeManager();
  whenAdding10ElementsWithSameIndex();
  thenPipeManagerSizeIsOne();

  printString("Testing multiple different additions\n",TB,TG,TR);

  givenAnInitializedPipeManager();
  whenAdding10ElementsWithDifferentIndex();
  thenPipeManagerSizeIsTen();

  printString("Testing existing removal\n",TB,TG,TR);

  givenAnInitializedPipeManager();
  given10AdditionsWithDifferentIndex();
  whenRemovingAnElementFromPipeManager();
  thenPipeManagerSizeIsNine();

  printString("Testing non-existing removal\n",TB,TG,TR);

  givenAnInitializedPipeManager();
  given10AdditionsWithDifferentIndex();
  whenRemovingANonExistingElement();
  thenPipeManagerSizeIsTen();

  finalizePipeManager();

}
