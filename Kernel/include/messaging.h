#ifndef MESSAGING_H
#define MESSAGING_H

#include "lib.h"
#include "semaphoreProcessQueue.h"

typedef struct mbd_t_Struct * mbd_t;
struct mbd_t_Struct
{
  size_t size;
  char block;
  void * key;
};

typedef struct messageStruct * message;
struct messageStruct
{
  message next;
  void * messageBody;
};

typedef struct messageBoxStruct * messageBox;
struct messageBoxStruct
{
  char * key;
  char block;
  message msg;
  size_t msgSize;
  messageBox next;
  queueEntry blocked;
};

typedef struct postOfficeStruct * postOfficePTR;
struct postOfficeStruct
{
  messageBox msgBox;
};

void initializePostOffice();
void finalizePostOffice();

int postOfficeSize();
int postOfficeSizeRec(messageBox * mB);

void initializeMessageBox(messageBox * mB, char * key_P, size_t size, char block_P);
void freeMessageBox(messageBox * mB);
void recursiveFinalizeMessageBox(messageBox *mB);

messageBox * findMessageBox(char * key_P, messageBox * mB);
int messageBoxSize(mbd_t descriptor);
int recMessageSize(message * mL);

messageBox getMessageBox(char * key_P, size_t messageSize,char block_P);
messageBox * getMessageBoxRec(char * key_P, messageBox * mB, size_t messageSize, char block_P);

void initializeMessage(message * m, void * messageContent, size_t messageSize);
void finalizeMessage(message * m);
void recursiveFinalizeMessage(message *mL);

void sendMessageRec(message * mL, size_t size, void * messageContent, messageBox * mB);
void recieveMessageRec(message * mL, size_t size, void *buffer, messageBox * mB);

//THESE ARE THE ONLY FUNCTIONS WHICH CAN BE USED FROM USERLAND
void finalizeMessageBox(mbd_t descriptor);
void sendMessage(mbd_t descriptor, void * messageContent);
void recieveMessage(mbd_t descriptor, void * buffer);

#endif
