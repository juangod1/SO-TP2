#ifndef PROCESSQUEUETEST_H
#define PROCESSQUEUETEST_H

void givenAnEmptyQueue();
void whenRemovingAnElement();
void thenElementRemovedIsMinusOne();
void thenQueueIsEmpty();
void givenAChangeInValue();
void static givenAPid();
void whenAddingAnElement();
void thenElementIsAdded();
void givenAnAddition();
void thenElementRemovedIsEqual();
void testCantRemoveWhenEmpty();
void testQueueAddition();
void testQueueRemoval();
void givenADifferentPid();
void givenADifferentAddition();
void thenElementIsEqualToFirst();
void thenQueueSizeIsOne();
void testThatRemoveRemovesFirst();
void processQueueTestMain();

#endif
