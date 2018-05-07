#ifndef MEMORYMANAGER_TEST_H
#define MEMORYMANAGER_TEST_H

#include "memorymanager.h"
#include "videoDriver.h"
#include <sys/types.h>
void mmTester();
void testSuccessfullInit();
void testNoMallocBefore();
void testMaxSize();
void testMaxMinusOneSize();
void testConsistentDualMalloc();
void testFree();

void givenAMemoryAddressBase();
void givenMaxSize();
void givenMaxMinusOneSize();
void givenTwoStrings();
void givenTwoStringsSameSize();

void whenMallocSize();
void whenMallocSizeOfBothStrings();
void whenWrittenBothStrings();
void whenAllocatingOne();
void whenAllocatingSecond();

void thenCheckMainBlockPid();
void thenVarIsNull();
void thenVarIsNotNull();
void thenCheckFirstBookBlockNull();
void thenCheckStringsAreConsistent();
void thenSaveAddressAndFreeFirst();
void thenCheckFirstAdressIsEqualToSecond();

void thenOk();
void thenFailed();

#endif
