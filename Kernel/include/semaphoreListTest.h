#ifndef SEMAPHORELISTTEST_H
#define SEMAPHORELISTTEST_H


void whenAddingAnElement();
void thenElementIsAdded();
void whenRemovingAnElement();
void thenItemisRemoved();
void givenAPreviousEqualElement();
void thenThereIsOnlyOneElement();
void givenAPreviousDifferentElement();
void thenThereIsTwoElements();
void givenThreeDifferentElements();
void thenTheRemovedElementIsRemoved();
void thenTheOtherElementsRemain();
void testlistAddition();
void testlistRemoval();
void testTwoSameKeyAdditions();
void testDifferentAdditions();
void testingExistanceAfterRemoval();
void semaphoreListTestMain();

#endif
