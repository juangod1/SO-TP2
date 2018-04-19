#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messaging.h"

void initializeMessageBox(messageBox * mB, char * key_P, size_t size)
{
  //string copy key_P to some other string that exists in kernel heap?
  (*mB)=malloc(sizeof(struct messageBoxStruct));
  (*mB)->key=key_P;
  (*mB)->msgList=NULL;
  (*mB)->msgSize=size;
  (*mB)->next=NULL;
}

void initializeMessageList(messageList * mL)
{
  (*mL)=malloc(sizeof(struct messageListStruct));
  (*mL)->msg=NULL;
  (*mL)->next=NULL;
}

void initializeMessage(message * m, void * messageContent)
{
  (*m) = malloc(sizeof(struct messageStruct));
  (*m)->messageBody=messageContent; //MIGHT HAVE TO MEMCPY LATER
}

void finalizeMessageList(messageList * mL)
{
  finalizeMessage(&((*mL)->msg));
  free(*mL);
  (*mL)=NULL;
}

void recursiveFinalizeMessageList(messageList *mL)
{
  if((*mL)!=NULL && (*mL)->next!=NULL)
  {
    recursiveFinalizeMessageList(&((*mL)->next));
  }
  finalizeMessageList(mL);
}

messageBox getMessageBox(char * key_P, messageBox mB)
{
  if(mB==NULL)
  {
    return NULL;
  }
  if(mB->key==key_P)
  {
    return mB;
  }
  return getMessageBox(key_P, mB->next);
}


void finalizeMessageBox(messageBox * mB)
{
  if((*mB)==NULL)
  {
    return;
  }
  recursiveFinalizeMessageList(&((*mB)->msgList));
  free(*mB);
  (*mB)=NULL;
}

void recursiveFinalizeMessageBox(messageBox *mB)
{
  if((*mB)!=NULL && (*mB)->next!=NULL)
  {
    recursiveFinalizeMessageBox(&((*mB)->next));
  }
  finalizeMessageBox(mB);
}

void finalizeMessage(message * m)
{
  if(m==NULL || (*m)==NULL) return;
  //free((*m)->messageBody);
  free(*m);
  (*m)=NULL;
}


void sendMessage(messageBox * mB, void * messageContent)
{
  sendMessageRec(&((*mB)->msgList), (*mB)->msgSize, messageContent);
}

void static sendMessageRec(messageList * mL, size_t size, void * messageContent)
{
  if((*mL)==NULL)
  {
    initializeMessageList(mL);
    message m;
    initializeMessage(&m, messageContent);
    (*mL)->msg=m;
    return;
  }
  sendMessageRec(&((*mL)->next),size,messageContent);
}

void recieveMessage(messageBox * mB, void * buffer)
{
  if(mB==NULL || *mB==NULL) return;
  recieveMessageRec(&((*mB)->msgList),(*mB)->msgSize,  buffer);
}

void recieveMessageRec(messageList * mL, size_t size, void *buffer)
{
  if(mL==NULL || (*mL)==NULL) return;
  messageList aux = (*mL)->next;
  memcpy(buffer, (*mL)->msg->messageBody, size);
  finalizeMessageList(mL);
  (*mL)=aux;
}




int messageBoxSize(messageBox * mB)
{
  if(mB==NULL || (*mB)==NULL) return 0;
  return recMessageListSize(&((*mB)->msgList));
}

int recMessageListSize(messageList * mL)
{
  if(mL ==NULL || (*mL)==NULL) return 0;
  return 1 + recMessageListSize(&((*mL)->next));
}
