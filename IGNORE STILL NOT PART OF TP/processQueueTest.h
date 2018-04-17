#ifndef PROCESSQUEUETEST_H
#define PROCESSQUEUETEST_H

void givenAnEmptyQueue();
void whenRemovingAnElement();
void thenElementRemovedIsMinusOne();
void thenQueueIsEmpty();
void givenAChangeInValue();
void givenAPid();
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

#endif
