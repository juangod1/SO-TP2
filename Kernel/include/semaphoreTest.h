#ifndef SEMAPHORETEST_H
#define SEMAPHORETEST_H


void givenAnEmptySemaphore();
void givenAPRocessPid();
void givenAnInitializedSemaphore();
void whenSemaphoreIsInitialized();
void whenSemaphoreIsFinalized();
void thenSemaphoreIsNoLongerNull();
void thenSemaphoreIsNull();
void whenRequestingATask();
void thenProcessQueueIsEmpty();
void thenSemaphoreValueIsZero();
void givenAPreviousTaskRequest();
void thenProcessQueueHasOneElement();
void thenSemaphoreValueIsMinusOne();
void semaphoreInitializationTest();
void semaphoreFinalizationTest();
void taskRequestTest();
void twoTasksRequestTest();
void setSemaphoreConditionsBackToNormal();
void semaphoreTestMain();

#endif
