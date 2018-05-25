#ifndef PIPETEST_H
#define PIPETEST_H


#include "testLib.h"
#include "pipe.h"


void givenANonInitializedPipe();
void whenInitializingPipe();
void givenAnInitializedPipe();
void whenAdding101elements();
void thenReadIndexIsOne();
void thenWriteIndexIsOne();
void thenCountIsOneHundred();
void given100Writes();
void given99Reads();
void whenReading();
void thenReadIndexIsZero();
void thenCountIsOne();


void pipeTestMain();


#endif
