#include "stdLib.h"
#include "messageBoxDemo.h"
#include "shell.h"

void senderProcess()
{
  sysPrintString("Entering senderProcess\n",CB,CG,CR);
  char * key="0123";
  int size=10;
  char block=1;
  struct mbd_t_Struct descriptor = {size,block,key};
  char * msg = "received?";
  sendMessage(&descriptor, msg);
  sysPrintString("Message sent!\n",CB,CG,CR);
  sysExit();
}
void receiverProcess()
{
  sysPrintString("Entering receiverProcess\n",CB,CG,CR);
  char * key="0123";
  int size=10;
  char block=1;
  struct mbd_t_Struct descriptor = {size, block,key};
  char buffer[10]={0};
  recieveMessage(&descriptor, buffer);
  sysPrintString("message received: ",CB,CG,CR);
  sysPrintString(buffer,CB,CG,CR);
  sysPrintString(".\n",CB,CG,CR);
  toggleForegroundSystem();
  sysExit();
}

void messageBoxDemoMain()
{
  toggleForegroundSystem();
  sysExecute(receiverProcess, "Consumer Process");
  sysExecute(senderProcess, "Sender Process");
} 
