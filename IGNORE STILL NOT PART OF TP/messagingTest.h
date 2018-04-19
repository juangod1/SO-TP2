#ifndef MESSAGINGTEST_H
#define MESSAGINGTEST_H


void givenAnInitializedMessageBox();
void givenAnInitializedMessageList();
void givenAMessage();
void whenAddingMessageToBox();
void thenMessageIsSent();
void givenAMessageAdded();
void whenReadingFromMessageBox();
void thenMessageBoxIsEmpty();
void thenMessageReadIsSame();
void givenAnIncorrectKey();
void givenACorrectKey();
void whenGettingAMessageBox();
void thenReceptionIsNull();
void thenReceptionIsNotNull();
void messageAdditionTest();
void messageReadTest();
void existingGetTest();
void nonExistingGetTest();
int messagingTestMain();

#endif
