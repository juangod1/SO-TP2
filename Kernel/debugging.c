#include "include/videoDriver.h"

void dumpStack(void* stackAdress)
{
    printString("__________________________________________________________________\n", 255, 0, 0);
    uint64_t *curr = (uint64_t *)stackAdress;
    printHex(curr, 0, 255, 0);
    printString("\n", 255, 0, 0);
    for (uint64_t i = 0; i < 20; i++)
    {
        printHex(curr[i], 255, 255, 255);
        printString("|",0,255,255);
        if(i%2 == 1)
            printString("\n", 255, 0, 0);
    }
    printString("__________________________________________________________________\n", 255, 0, 0);
}

void dumpStackAndHalt(void* stackAdress)
{
    printString("__________________________________________________________________\n", 255, 0, 0);
    uint64_t *curr = (uint64_t *)stackAdress;
    printHex(curr, 0, 255, 0);
    printString("\n", 255, 0, 0);
    for (uint64_t i = 0; i < 20; i++)
    {
        printHex(curr[i], 255, 255, 255);
        printString("\n",0,0,0);
    }
    printString("__________________________________________________________________\n", 255, 0, 0);
    while(1);
}


void processorWait(int number){
    number = number*1000;
    while(number){number--;};
}