#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messaging.h"


/*TODO
- MESSAGE BOX FINALIZATION API MUST BE COHERENT WITH HEADER REFERENCE OF POST OFFICE
- FINALIZATION BY KEY OF NON EXISTING MESSAGE BOXS MUST NOT LEAK
- FINALIZATION BY KEY IN AN ORDER DIFFERENT THAN THE ONE GIVEN MUST NOT LEAK
- RECEIVE MESSAGE MUST STOP PROCESS JUST LIKE SEMAPHORE
-
*/
postOfficePTR postOffice;

void initializePostOffice()
{
  if(postOffice!=NULL)
  {
    return;
  }
  postOffice=malloc(sizeof(struct postOfficeStruct));
  postOffice->msgBox=malloc(sizeof(void *));
  *(postOffice->msgBox)=NULL;
}

void finalizePostOffice()
{
  if(postOffice==NULL)
  {
    return;
  }
  recursiveFinalizeMessageBox(postOffice->msgBox);
  free(postOffice->msgBox);
  postOffice->msgBox=NULL;
  free(postOffice);
  postOffice=NULL;
}

void initializeMessageBox(messageBox * mB, char * key_P, size_t size)
{
  (*mB)=malloc(sizeof(struct messageBoxStruct));
  (*mB)->key=key_P;
  (*mB)->msg=NULL;
  (*mB)->msgSize=size;
  (*mB)->next=NULL;

}


void initializeMessage(message * m, void * messageContent, size_t messageSize)
{
  (*m) = malloc(sizeof(struct messageStruct));
  (*m)->messageBody = malloc(messageSize);
  memcpy((*m)->messageBody, messageContent, messageSize);
  (*m)->next=NULL;
}

void freeMessageBox(messageBox * mB)
{
  if((*mB)==NULL)
  {
    return;
  }
  recursiveFinalizeMessage(&((*mB)->msg));
  (*mB)->next=NULL;
  free(*mB);
  (*mB)=NULL;
}

void finalizeMessageBox(char * key_P)
{
  messageBox * del = findMessageBox(key_P, postOffice->msgBox);
  freeMessageBox(del);
}

void recursiveFinalizeMessageBox(messageBox *mB)
{
  if((*mB)!=NULL)
  {
    recursiveFinalizeMessageBox(&((*mB)->next));
  }
  freeMessageBox(mB);
}

void recursiveFinalizeMessage(message *mL)
{
  if((*mL)!=NULL)
  {
    recursiveFinalizeMessage(&((*mL)->next));
  }
  finalizeMessage(mL);
}


void finalizeMessage(message * m)
{
  if(m==NULL || (*m)==NULL)
  {
    return;
  }
  free((*m)->messageBody);
  free(*m);
  (*m)=NULL;
}


void sendMessage(messageBox * mB, void * messageContent)
{
  sendMessageRec(&((*mB)->msg), (*mB)->msgSize, messageContent);
}

void static sendMessageRec(message * mL, size_t size, void * messageContent)
{
  if((*mL)==NULL)
  {
    initializeMessage(mL, messageContent, size);
    return;
  }
  sendMessageRec(&((*mL)->next),size,messageContent);
}

void recieveMessage(messageBox * mB, void * buffer)
{
  if(mB==NULL || *mB==NULL) return;
  recieveMessageRec(&((*mB)->msg),(*mB)->msgSize,  buffer);
}

void recieveMessageRec(message * mL, size_t size, void *buffer)
{
  if(mL==NULL || (*mL)==NULL) return;
  message aux = (*mL)->next;
  memcpy(buffer, (*mL)->messageBody, size);
  finalizeMessage(mL);
  (*mL)=aux;
}

int messageBoxSize(messageBox * mB)
{
  if(mB==NULL || (*mB)==NULL) return 0;
  return recMessageSize(&((*mB)->msg));
}

int recMessageSize(message * mL)
{
  if(mL ==NULL || (*mL)==NULL) return 0;
  return 1 + recMessageSize(&((*mL)->next));
}

messageBox getMessageBox(char * key_P, size_t messageSize)
{
  return getMessageBoxRec(key_P, postOffice->msgBox, messageSize);
}

messageBox getMessageBoxRec(char * key_P, messageBox * mB, size_t messageSize)
{
  if((*mB)==NULL)
  {
    initializeMessageBox(mB, key_P, messageSize);
    return (*mB);
  }
  if((*mB)->key==key_P)
  {
    return *mB;
  }
  return getMessageBoxRec(key_P, (&(*mB)->next), messageSize);
}

messageBox * findMessageBox(char * key_P, messageBox * mB)
{
  if((*mB)==NULL)
  {
    return NULL;
  }
  if((*mB)->key==key_P)
  {
    return mB;
  }
  return findMessageBox(key_P, (&(*mB)->next));
}
