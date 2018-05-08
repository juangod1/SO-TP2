#include "include/testLib.h"
#include "include/messaging.h"
#include "include/messagingTest.h"
#include "include/lib.h"
#include "include/memorymanager.h"
#include "include/scheduler.h"

message global_message;
int global_size = 5;
mbd_t global_MB_descriptor=NULL;
mbd_t different_global_MB_descriptor=NULL;
void * global_buffer=NULL;


void givenAMessageBox()
{
  sendMessage(global_MB_descriptor, global_message);
}
void givenAnotherMessageBox()
{
  sendMessage(different_global_MB_descriptor, global_message);
}

void givenAnInitializedPostOffice()
{
  initializePostOffice();
}

void givenADifferentDescriptor()
{
  if(different_global_MB_descriptor!=NULL) return;
  different_global_MB_descriptor=malloc(sizeof(struct mbd_t_Struct));
  different_global_MB_descriptor->key=(void*)"diff";
  different_global_MB_descriptor->size=global_size;
}

void givenAMessage()
{
  global_message=(void*)"okay";
}

void whenAddingMessageToBox()
{
  sendMessage(global_MB_descriptor,global_message);
}


void whenDeletingAMessageBox()
{
  finalizeMessageBox(different_global_MB_descriptor);
}


void thenMessageBoxIsRemoved()
{
  if(postOfficeSize()==1)
  {
    ok();
  }
  else
  {
    printInt(postOfficeSize(),0,255,255);
    fail("Expected postOffice size equal to one, found different number\n");
  }
}

void thenMessageIsSent()
{
  if(messageBoxSize(global_MB_descriptor)==1)
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
  sendMessage(global_MB_descriptor,global_message);
}

void whenReadingFromMessageBox()
{
  global_buffer=malloc(5);
  recieveMessage(global_MB_descriptor,global_buffer);
}

void thenMessageBoxIsEmpty()
{
  if(messageBoxSize(global_MB_descriptor)==0)
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
    fail("Expected string 'okay', found another string\n");
  }
}

void givenACorrectDescriptor()
{
  if(global_MB_descriptor!=NULL) return;
  global_MB_descriptor=malloc(sizeof(struct mbd_t_Struct));
  global_MB_descriptor->key=(void*)"okay";
  global_MB_descriptor->size=global_size;
}



void messageAdditionTest()
{
  givenAnInitializedPostOffice();
  givenAMessage();
  givenACorrectDescriptor();
  whenAddingMessageToBox();
  thenMessageIsSent();
}

void messageReadTest()
{
  givenAnInitializedPostOffice();
  givenACorrectDescriptor();
  givenAMessage();
  givenAMessageAdded();
  whenReadingFromMessageBox();
  thenMessageBoxIsEmpty();
  thenMessageReadIsSame();
}

void deletionInDifferentOrderTest()
{
  givenAnInitializedPostOffice();
  givenACorrectDescriptor();
  givenADifferentDescriptor();
  givenAMessageBox();
  givenAnotherMessageBox();
  whenDeletingAMessageBox();
  thenMessageBoxIsRemoved();
}

void givenNoAdditions(){}
void thenNothinigHappens(){ok();}

void nonExistingKeyDeletion()
{
  givenAnInitializedPostOffice();
  givenNoAdditions();
  whenDeletingAMessageBox();
  thenNothinigHappens();
}

void whenAddingAHundredMessages()
{
  for(int i=0; i<100; i++){
    sendMessage(global_MB_descriptor, global_message);
  }
}

void thenSizeIsHundred()
{
  if(messageBoxSize(global_MB_descriptor)==100)
  {
    ok();
  }
  else
  {
    fail("Expected size equal to 100 found different size\n");
  }
}

void  hundredAdditionsTest()
{
  givenAnInitializedPostOffice();
  givenACorrectDescriptor();
  whenAddingAHundredMessages();
  thenSizeIsHundred();
}

void whenDeletingAHundredMessages()
{
  finalizeMessageBox(global_MB_descriptor);
}

void thenSizeIsZero()
{
  if(messageBoxSize(global_MB_descriptor)==0)
  {
    ok();
  }
  else
  {
    fail("Expected size equal to 0 found different size\n");
  }
}

void hundredDeletionsTest()
{
  whenDeletingAHundredMessages();
  thenSizeIsZero();
}

void whenAddingAHundredMessageBoxs()
{
  for (int i=0; i<100; i++)
  {
    char * str=malloc(5);
    str[0]='0'+i%10;
    str[1]='0'+i/10;
    str[2]='0'+i%10;
    str[3]='0'+i/10;
    str[4]=0;
    mbd_t descriptor=malloc(sizeof(struct mbd_t_Struct));
    descriptor->key=str;
    descriptor->size=global_size;
    descriptor->block=0;
    sendMessage(descriptor, global_message);
    free(str);
    free(descriptor);
  }
}

void hundredMessageBoxAdditionsTest()
{
  givenACorrectDescriptor();
  givenAMessage();
  givenAnInitializedPostOffice();
  whenAddingAHundredMessageBoxs();
  thenPostOfficeSizeIsAHundred();
}


void thenPostOfficeSizeIsAHundred()
{
  if(postOfficeSize()==100)
  {
    ok();
  }
  else
  {
    fail("Expected postOfficeSize equal to 100, found different number\n");
  }
}

void resetConditions()
{
  finalizePostOffice();
  free(global_MB_descriptor);
  global_MB_descriptor=NULL;
  free(different_global_MB_descriptor);
  different_global_MB_descriptor=NULL;
  free(global_buffer);
  global_buffer=NULL;
}



void messagingTestMain()
{
  //printString("Testing message addition --> ",TB,TG,TR);
  messageAdditionTest();
  resetConditions();
  //printString("Testing message reception --> ",TB,TG,TR);
  messageReadTest();
  resetConditions();
  //printString("Test deletion in a different order of messageBox --> ",TB,TG,TR);
  deletionInDifferentOrderTest();
  resetConditions();
  //printString("Test non existing message box deletion --> ",TB,TG,TR);
  nonExistingKeyDeletion();
  resetConditions();
  //printString("Test a hundred additions --> ",TB,TG,TR);
  hundredAdditionsTest();
  resetConditions();
  //printString("Test a hundred messageBox additions --> ",TB,TG,TR);
  hundredMessageBoxAdditionsTest();
  resetConditions();
}
