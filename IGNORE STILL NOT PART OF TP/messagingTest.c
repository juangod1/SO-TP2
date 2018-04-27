#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testlib.h"
#include "messaging.h"

messageBox global_Message_Box;
messageBox different_Global_Message_Box;
messageBox reception_global_Message_Box;
message global_message;
int global_size = 5;
void * global_buffer;
char * global_MB_key;

void givenAnInitializedPostOffice()
{
  initializePostOffice();
}


void givenADifferentCreatedMessageBox()
{
  different_Global_Message_Box=getMessageBox("different", global_size);
}

void givenACreatedMessageBox()
{
  global_Message_Box=getMessageBox("ok", global_size);
}

void givenAMessage()
{
  global_message=(void*)"okay";
}

void whenAddingMessageToBox()
{
  sendMessage(&global_Message_Box,  global_message);
}


void whenDeletingAMessageBox()
{
  finalizeMessageBox("different");
}


void thenMessageBoxIsRemoved()
{
  if(postOfficeSize()==1)
  {
    ok();
  }
  else
  {
    fail("Expected postOffice size equal to one, found different number");
  }
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

void givenACorrectKey()
{
  global_MB_key="ok";
}

void whenGettingAMessageBox()
{
  reception_global_Message_Box=getMessageBox(global_MB_key, global_size);
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
  givenAnInitializedPostOffice();
  givenAMessage();
  givenACreatedMessageBox();
  whenAddingMessageToBox();
  thenMessageIsSent();
}

void messageReadTest()
{
  givenAnInitializedPostOffice();
  givenACreatedMessageBox();
  givenAMessageAdded();
  whenReadingFromMessageBox();
  thenMessageBoxIsEmpty();
  thenMessageReadIsSame();
}

void existingGetTest()
{
  givenAnInitializedPostOffice();
  givenACreatedMessageBox();
  givenACorrectKey();
  whenGettingAMessageBox();
  thenReceptionIsNotNull();
}

void deletionInDifferentOrderTest()
{
  givenAnInitializedPostOffice();
  givenACreatedMessageBox();
  givenADifferentCreatedMessageBox();
  whenDeletingAMessageBox();
  thenMessageBoxIsRemoved();
}

void givenNoAdditions(){}
void thenNothinigHappens(){ok();}

void nonExistingKeyDeletion()
{
  givenNoAdditions();
  whenDeletingAMessageBox();
  thenNothinigHappens();
}


int messagingTestMain()
{
  printf("Testing message addition\n");
  messageAdditionTest();
  finalizeMessageBox("ok");
  printf("Testing message reception\n");
  messageReadTest();
  finalizeMessageBox("ok");
  free(global_buffer);
  printf("Test get an existing messageBox\n");
  existingGetTest();
  finalizeMessageBox("ok");
  printf("Test deletion in a different order of messageBox\n");
  deletionInDifferentOrderTest();
  finalizeMessageBox("ok");
  printf("Test non existing message box deletion\n");
  nonExistingKeyDeletion();

  finalizePostOffice();

}
