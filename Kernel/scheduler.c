//
// Created by juangod on 18/04/18.
//

#include <stdint.h>
#include <stdio.h>
#include "include/process.h"
#include "include/processQueue.h"

void initialize_stack_frame(uint64_t initialBSP);
uint64_t* get_eip();

uint64_t kernelTableAddress = 0x0; //placeholder
process_t currentProcess = NULL;
pid_t lastPid;

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
        perror("Malloc process queue error\n");
    if(ret==-2)
        perror("received null process\n");
    return ret;
}

pid_t getNewPid()
{
    lastPid = lastPid + 1;
    return lastPid;
}

void destroyProcessQueue(){
    destroyQueue();
}

uint64_t schedule(uint64_t* prevSBP)
{
    process_t currentProcess = getCurrentProcess();
    process_t nextProcess = getNextProcess();

    currentProcess->context->stackBasePointer = prevSBP;
    return nextProcess->context->stackBasePointer;
}

void initializeProcess(uint64_t* eip)
{
    process_t newProcess = malloc(512);
    newProcess->pid = getNewPid();
    newProcess->context->stackBasePointer = malloc(1024);
    initialize_stack_frame(eip);
    queueProcess(newProcess);
}

void exec(uint64_t* eip)
{
    process_t newProcess = malloc(512);
    newProcess->pid = getNewPid();
    newProcess->context->stackBasePointer = malloc(2048);
    initialize_stack_frame(eip);
    queueProcess(newProcess);
}

void initializeProcessStackFrame(uint64_t* initialEIP)
{
    initialize_stack_frame(initialEIP);
}