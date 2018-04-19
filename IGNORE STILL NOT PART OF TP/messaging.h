#ifndef MESSAGING_H
#define MESSAGING_H


typedef struct messageStruct * message;
struct messageStruct
{
  //int src; //HAS TO BE PID TYPE EVENTUALLY
  //int dest; //HAS TO BE PID TYPE EVENTUALLY
  void * messageBody;
};

typedef struct messageListStruct * messageList;
struct messageListStruct
{
  message msg;
  messageList next;
};


typedef struct messageBoxStruct * messageBox;
struct messageBoxStruct
{
  char * key;
  messageList msgList;
  size_t msgSize;
  messageBox next;
};


void initializeMessageBox(messageBox * mB, char * key_P, size_t size);
void initializeMessageList(messageList * mL);
void finalizeMessageList(messageList * mL);
void recursiveFinalizeMessageList(messageList *mL);
void finalizeMessageBox(messageBox * mB);
void recursiveFinalizeMessageBox(messageBox *mB);
void finalizeMessage(message * m);
void sendMessage(messageBox * mb, void * messageContent);
void static sendMessageRec(messageList * mL, size_t size, void * messageContent);
void recieveMessage(messageBox * mb, void * buffer);
void recieveMessageRec(messageList * mL, size_t size, void * buffer);
int messageBoxSize(messageBox * mB);
int recMessageListSize(messageList * mL);
void initializeMessage(message * m, void * messageContent);
messageBox getMessageBox(char * key_P, messageBox mB);

#endif
