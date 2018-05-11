#ifndef DEBUGGING_H
#define DEBUGGING_H

#include "videoDriver.h"

void dumpStackAndHalt(void *stackAdress);
void dumpStack(void *stackAdress);
void processorWait(int number);


#endif
