#ifndef MESSAGING_H
#define MESSAGING_H


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
  size_t msgSize;
  messageBox next;
};

typedef struct postOfficeStruct * postOfficePTR;
struct postOfficeStruct
{
  messageBox * msgBox;
};

void initializeMessageBox(messageBox * mB, char * key_P, size_t size);
void finalizeMessageBox(char * key_P);
void recursiveFinalizeMessageBox(messageBox *mB);
void freeMessageBox(messageBox * mB);


void initializeMessage(message * mL, void * messageBody, size_t size);
void finalizeMessage(message * mL);
void recursiveFinalizeMessage(message *mL);

void sendMessage(messageBox * mb, void * messageContent);
void static sendMessageRec(message * mL, size_t size, void * messageContent);
void recieveMessage(messageBox * mb, void * buffer);
void recieveMessageRec(message * mL, size_t size, void * buffer);
int messageBoxSize(messageBox * mB);
int recMessageSize(message * mL);
messageBox getMessageBox(char * key_P, size_t messageSize);
messageBox getMessageBoxRec(char * key_P, messageBox * mB, size_t messageSize);

messageBox * findMessageBox(char * key_P, messageBox * mB);

void initializePostOffice();

#endif
