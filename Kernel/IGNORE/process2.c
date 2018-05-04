#include "messaging.h"
#include "semaphore.h"
#include "process2.h"
#include <stdio.h>
#include <stdlib.h>

void process2()
{
  char * key="0123";
  int size=10;
  struct mbd_t_Struct descriptor = {size,key};
  char buffer[10]={0};
  recieveMessage(&descriptor, buffer);
  printf("message received %s\n", buffer);
}
