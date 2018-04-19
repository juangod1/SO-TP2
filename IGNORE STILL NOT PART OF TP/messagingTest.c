#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testlib.h"
#include "messaging.h"

messageBox global_Message_Box;
messageBox reception_global_Message_Box;
message global_message;
void * global_buffer;
char * global_MB_key;

void givenAnInitializedMessageBox()
{
  initializeMessageBox(&global_Message_Box, "ok", 5);
}

void givenAnInitializedMessageList()
{
  initializeMessageList(&(global_Message_Box->msgList));
}

void givenAMessage()
{
  global_message=(void*)"okay";
}

void whenAddingMessageToBox()
{
  sendMessage(&global_Message_Box, global_message);
}

void thenMessageIsSent()
{
  if(messageBoxSize(&global_Message_Box)==1)
  {
    ok();
  }
  else
  {
    fail("Expected message box size one, found different message box size\n");
  }
}

void givenAMessageAdded()
{
  givenAMessage();
  sendMessage(&global_Message_Box, global_message);
}

void whenReadingFromMessageBox()
{
  global_buffer=malloc(5);
  recieveMessage(&global_Message_Box, global_buffer);
}

void thenMessageBoxIsEmpty()
{
  if(messageBoxSize(&global_Message_Box)==0)
  {
    ok();
  }
  else
  {
    fail("Expected empty message box, found non-empty message box\n");
  }
}

void thenMessageReadIsSame()
{
  if(strcmp(global_buffer, "okay")==0)
  {
    ok();
  }
  else
  {
    fail("Expected string 'okay', found another string");
  }
}

void givenAnIncorrectKey()
{
  global_MB_key="incorrect";
}

void givenACorrectKey()
{
  global_MB_key="ok";
}

void whenGettingAMessageBox()
{
  reception_global_Message_Box=getMessageBox(global_MB_key, global_Message_Box);
}

void thenReceptionIsNull()
{
  if(reception_global_Message_Box==NULL)
  {
    ok();
  }
  else
  {
    fail("Expected a null Message box, found non null Message box\n");
  }
}

void thenReceptionIsNotNull()
{
  if(reception_global_Message_Box!=NULL)
  {
    ok();
  }
  else
  {
    fail("Expected a non null Message box, found null Message box\n");
  }
}

void messageAdditionTest()
{
  givenAnInitializedMessageBox();
  givenAMessage();
  whenAddingMessageToBox();
  thenMessageIsSent();
}

void messageReadTest()
{
  givenAnInitializedMessageBox();
  givenAMessageAdded();
  whenReadingFromMessageBox();
  thenMessageBoxIsEmpty();
  thenMessageReadIsSame();
}

void existingGetTest()
{
  givenAnInitializedMessageBox();
  givenACorrectKey();
  whenGettingAMessageBox();
  thenReceptionIsNotNull();
}

void nonExistingGetTest()
{
  givenAnInitializedMessageBox();
  givenAnIncorrectKey();
  whenGettingAMessageBox();
  thenReceptionIsNull();
}

int messagingTestMain()
{
  printf("Testing message addition\n");
  messageAdditionTest();
  recursiveFinalizeMessageBox(&global_Message_Box);
  printf("Testing message reception\n");
  messageReadTest();
  recursiveFinalizeMessageBox(&global_Message_Box);
  free(global_buffer);
  printf("Test get an existing messageBox\n");
  existingGetTest();
  recursiveFinalizeMessageBox(&global_Message_Box);
  printf("Test get a non existing messageBox\n");
  nonExistingGetTest();
  recursiveFinalizeMessageBox(&global_Message_Box);

}
