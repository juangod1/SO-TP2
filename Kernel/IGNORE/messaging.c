#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messaging.h"

#define MBKEYSIZE 5

/*TODO
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

int postOfficeSize()
{
  if(postOffice==NULL)
  {
    return 0;
  }
  return postOfficeSizeRec(postOffice->msgBox);
}

int postOfficeSizeRec(messageBox * mB)
{
  if((*mB)==NULL)
  {
    return 0;
  }
  return 1 + postOfficeSizeRec(&((*mB)->next));
}




void initializeMessageBox(messageBox * mB, char * key_P, int size)
{
  (*mB)=malloc(sizeof(struct messageBoxStruct));
  char * mbKey=malloc(MBKEYSIZE);
  memcpy(mbKey, key_P, MBKEYSIZE);
  (*mB)->key=mbKey;
  (*mB)->msg=NULL;
  (*mB)->msgSize=size;
  (*mB)->next=NULL;

}

void freeMessageBox(messageBox * mB)
{
  if((*mB)==NULL)
  {
    return;
  }
  recursiveFinalizeMessage(&((*mB)->msg));
  messageBox aux = (*mB)->next;
  (*mB)->next=NULL;
  free((*mB)->key);
  free(*mB);
  (*mB)=aux;
}

void recursiveFinalizeMessageBox(messageBox *mB)
{
  if((*mB)!=NULL)
  {
    recursiveFinalizeMessageBox(&((*mB)->next));
  }
  freeMessageBox(mB);
}



messageBox * findMessageBox(char * key_P, messageBox * mB)
{
  if((*mB)==NULL)
  {
    return NULL;
  }
  if(memcmp((*mB)->key,key_P, 5)==0)
  {
    return mB;
  }
  return findMessageBox(key_P, (&(*mB)->next));
}

int messageBoxSize(mbd_t descriptor)
{
  messageBox * mB = getMessageBoxRec(descriptor->key, postOffice->msgBox, descriptor->size);
  if(mB==NULL || (*mB)==NULL) return 0;
  return recMessageSize(&((*mB)->msg));
}

int recMessageSize(message * mL)
{
  if(mL ==NULL || (*mL)==NULL) return 0;
  return 1 + recMessageSize(&((*mL)->next));
}



messageBox getMessageBox(char * key_P, int messageSize)
{
  return *(getMessageBoxRec(key_P, postOffice->msgBox, messageSize));
}

messageBox * getMessageBoxRec(char * key_P, messageBox * mB, int messageSize)
{
  if((*mB)==NULL)
  {
    initializeMessageBox(mB, key_P, messageSize);
    return mB;
  }
  if(memcmp((*mB)->key,key_P, 5)==0)
  {
    return mB;
  }
  return getMessageBoxRec(key_P, (&(*mB)->next), messageSize);
}



void initializeMessage(message * m, void * messageContent, int messageSize)
{
  (*m) = malloc(sizeof(struct messageStruct));
  (*m)->messageBody = malloc(messageSize);
  memcpy((*m)->messageBody, messageContent, messageSize);
  (*m)->next=NULL;
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

void recursiveFinalizeMessage(message *mL)
{
  if((*mL)!=NULL)
  {
    recursiveFinalizeMessage(&((*mL)->next));
  }
  finalizeMessage(mL);
}



void sendMessageRec(message * mL, int size, void * messageContent)
{
  if((*mL)==NULL)
  {
    initializeMessage(mL, messageContent, size);
    return;
  }
  sendMessageRec(&((*mL)->next),size,messageContent);
}

void recieveMessageRec(message * mL, int size, void *buffer)
{
  if(mL==NULL || (*mL)==NULL) return;//
  message aux = (*mL)->next;
  memcpy(buffer, (*mL)->messageBody, size);
  finalizeMessage(mL);
  (*mL)=aux;
}



void finalizeMessageBox(mbd_t descriptor)
{
  messageBox * del = findMessageBox(descriptor->key, postOffice->msgBox);
  if(del!=NULL)  freeMessageBox(del);
}

void sendMessage(mbd_t descriptor, void * messageContent)
{
  messageBox * mB = getMessageBoxRec(descriptor->key, postOffice->msgBox, descriptor->size);
  if(mB==NULL || *mB==NULL) return;
  sendMessageRec(&((*mB)->msg), (*mB)->msgSize, messageContent);
}

void recieveMessage(mbd_t descriptor, void * buffer)
{
  messageBox * mB = getMessageBoxRec(descriptor->key, postOffice->msgBox, descriptor->size);
  if(mB==NULL || *mB==NULL) return;
  recieveMessageRec(&((*mB)->msg),(*mB)->msgSize,  buffer);
}
