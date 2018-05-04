#ifndef MESSAGING_H
#define MESSAGING_H

typedef struct mbd_t_Struct * mbd_t;
struct mbd_t_Struct
{
  int size;
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
  message msg;
  int msgSize;
  messageBox next;
};

typedef struct postOfficeStruct * postOfficePTR;
struct postOfficeStruct
{
  messageBox * msgBox;
};

void initializePostOffice();
void finalizePostOffice();

int postOfficeSize();
int postOfficeSizeRec(messageBox * mB);

void initializeMessageBox(messageBox * mB, char * key_P, int size);
void freeMessageBox(messageBox * mB);
void recursiveFinalizeMessageBox(messageBox *mB);

messageBox * findMessageBox(char * key_P, messageBox * mB);
int messageBoxSize(mbd_t descriptor);
int recMessageSize(message * mL);

messageBox getMessageBox(char * key_P, int messageSize);
messageBox * getMessageBoxRec(char * key_P, messageBox * mB, int messageSize);

void initializeMessage(message * m, void * messageContent, int messageSize);
void finalizeMessage(message * m);
void recursiveFinalizeMessage(message *mL);

void sendMessageRec(message * mL, int size, void * messageContent);
void recieveMessageRec(message * mL, int size, void *buffer);

//THESE ARE THE ONLY FUNCTIONS WHICH CAN BE USED FROM USERLAND
void finalizeMessageBox(mbd_t descriptor);
void sendMessage(mbd_t descriptor, void * messageContent);
void recieveMessage(mbd_t descriptor, void * buffer);

#endif
