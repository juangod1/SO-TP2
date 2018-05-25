#ifndef PIPEMANAGERTEST_H
#define PIPEMANAGERTEST_H

#include "pipeManager.h"
#include "testlib.h"


void givenAnInitializedPipeManager();
void whenAdding10ElementsWithSameIndex();
void thenPipeManagerSizeIsOne();
void whenAdding10ElementsWithDifferentIndex();
void thenPipeManagerSizeIsTen();
void given10AdditionsWithDifferentIndex();
void whenRemovingAnElement();
void thenPipeManagerSizeIsNine();
void whenRemovingANonExistingElement();
int pipeManagerTestMain();

#endif
