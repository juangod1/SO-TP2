#ifndef PIPEMANAGERTEST_H
#define PIPEMANAGERTEST_H

#include "pipeManager.h"
#include "testLib.h"


void givenAnInitializedPipeManager();
void whenAdding10ElementsWithSameIndex();
void thenPipeManagerSizeIsOne();
void whenAdding10ElementsWithDifferentIndex();
void thenPipeManagerSizeIsTen();
void given10AdditionsWithDifferentIndex();
void whenRemovingAnElementFromPipeManager();
void thenPipeManagerSizeIsNine();
void whenRemovingANonExistingElement();
void pipeManagerTestMain();

#endif
