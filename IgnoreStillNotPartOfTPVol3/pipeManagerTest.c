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

void whenRemovingAnElement()
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

int pipeManagerTestMain()
{
  printf("Entering pipeManager test\n");
  printf("Testing multiple same additions\n");
  givenAnInitializedPipeManager();
  whenAdding10ElementsWithSameIndex();
  thenPipeManagerSizeIsOne();

  printf("Testing multiple different additions\n");

  givenAnInitializedPipeManager();
  whenAdding10ElementsWithDifferentIndex();
  thenPipeManagerSizeIsTen();

  printf("Testing existing removal\n");

  givenAnInitializedPipeManager();
  given10AdditionsWithDifferentIndex();
  whenRemovingAnElement();
  thenPipeManagerSizeIsNine();

  printf("Testing non-existing removal\n");

  givenAnInitializedPipeManager();
  given10AdditionsWithDifferentIndex();
  whenRemovingANonExistingElement();
  thenPipeManagerSizeIsTen();

  finalizePipeManager();

}
