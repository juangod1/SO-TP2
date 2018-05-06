#ifndef MEMORYMANAGER_TEST_H
#define MEMORYMANAGER_TEST_H

#include "memorymanager.h"
void mmTester();
void testSuccessfullInit();
void testNoMallocBefore();
void testMaxSize();
void testMaxMinusOneSize();

void givenAMemoryAddressBase();
void givenMaxSize();
void givenMaxMinusOneSize();

void whenMallocSize();

void thenCheckMainBlockPid();
void thenVarIsNull();
void thenVarIsNotNull();
void thenCheckFirstBookBlockNull();

void thenOk();
void thenFailed();

#endif
