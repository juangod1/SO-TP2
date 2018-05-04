#include "messaging.h"
#include "semaphore.h"
#include "process1.h"
#include <stdio.h>
#include <stdlib.h>

void process1()
{
  char * key="0123";
  int size=10;
  struct mbd_t_Struct descriptor = {size,key};
  char * msg = "received?";
  sendMessage(&descriptor, msg);
}
