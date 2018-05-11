#include "stdLib.h"
#include "messageBoxDemo.h"
#include "shell.h"

void senderProcess()
{
  sysPrintString("b1\n",CB,CG,CR);
  char * key="0123";
  int size=10;
  char block=1;
  struct mbd_t_Struct descriptor = {size,block,key};
  char * msg = "received?";
  sysPrintString("b2\n",CB,CG,CR);
  sendMessage(&descriptor, msg);
  sysPrintString("b3\n",CB,CG,CR);
  sysPrintString("Message sent!\n",CB,CG,CR);
}
void receiverProcess()
{
  sysPrintString("c1\n",CB,CG,CR);
  char * key="0123";
  int size=10;
  char block=1;
  struct mbd_t_Struct descriptor = {size, block,key};
  char buffer[10]={0};
  sysPrintString("c2\n",CB,CG,CR);
  recieveMessage(&descriptor, buffer);
  sysPrintString("message received: ",CB,CG,CR);
  sysPrintString(buffer,CB,CG,CR);
  sysPrintString(".\n",CB,CG,CR);
}

void messageBoxDemoMain()
{
  toggleForegroundSystem();
  sysPrintString("a1\n",CB,CG,CR);
  sysExecute(senderProcess, "Sender Process");
  sysPrintString("a2\n",CB,CG,CR);
  sysExecute(receiverProcess, "Consumer Process");
}
