//
// Created by juangod on 18/04/18.
//

#include <stdint.h>
#include <stdio.h>
#include "process.h"
#include "processQueue.h"

uint64_t kernelTableAddress = 0x0; //placeholder
process_t currentProcess = NULL;

pid_t getPid(){
    return currentProcess->pid;
}

process_t getCurrentProcess(){
    return currentProcess;
}

// Returns -1 if PID not found, 0 if slept, 1 if already sleeping
int sleepProcess(pid_t pid){
    process_t find = peekByPID(pid);
    if (find==NULL)
        return -1;

    if(find->sleeps)
        return 1;

    find->sleeps = 1;
    return 0;
}

// Returns -1 if PID not found, 0 if woke up, 1 if already woke
int wakeProcess(pid_t pid){
    process_t find = peekByPID(pid);
    if (find==NULL)
        return -1;

    if(!find->sleeps)
        return 1;

    find->sleeps = 0;
    return 0;
}

process_t getNextProcess(){
    process_t next = poll(1);
    currentProcess = next;
    return next;
}

int getAmountOfProcesses(){
   return getQueueSize();
}

void listProcesses(){
    listQueue();
}

int queueProcess(process_t process){
    int ret = add(process);
    if(ret==-1)
        perror("Malloc process queue error");
    if(ret==-2)
        perror("received null process");
    return ret;
}

void destroyProcessQueue(){
    destroyQueue();
}