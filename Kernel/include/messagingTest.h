#ifndef MESSAGINGTEST_H
#define MESSAGINGTEST_H

#include "testLib.h"
#include "messaging.h"
#include "lib.h"
#include "memorymanager.h"
#include "videoDriver.h"
#include "scheduler.h"

void givenAnInitializedMessageBox();
void givenAnInitializedmessage();
void givenAMessage();
void whenAddingMessageToBox();
void thenMessageIsSent();
void givenAMessageAdded();
void whenReadingFromMessageBox();
void thenMessageBoxIsEmpty();
void thenMessageReadIsSame();
void givenACorrectDescriptor();
void whenGettingAMessageBox();
void thenReceptionIsNull();
void thenReceptionIsNotNull();
void messageAdditionTest();
void messageReadTest();
void existingGetTest();
void messagingTestMain();
void thenPostOfficeSizeIsAHundred();

#endif
