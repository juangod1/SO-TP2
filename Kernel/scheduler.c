//
// Created by juangod on 18/04/18.
//
#include "include/process.h"
#include "include/memorymanager.h"
#include "include/processQueue.h"
#include "include/videoDriver.h"

void initialize_stack_frame(uint64_t initialBSP);
uint64_t* get_eip();

uint64_t kernelTableAddress = 0x0; //placeholder
process_t currentProcess = NULL;
pid_t lastPid;

pid_t getPid(pid_t* pid){
    if(currentProcess == NULL)
        *pid = -1;
    *pid = currentProcess->pid;
    return;
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
    // printString("Number of processes scheduled:",255,255,255);
    // printInt(getAmountOfProcesses(),255,255,255);
    // printString("\n",0,0,0);
    process_t currentProcess = getCurrentProcess();
    process_t nextProcess = getNextProcess();

    if(currentProcess == NULL || nextProcess == NULL)
    {    
        // printString("One or zero processes.\n",255,255,255);
        return prevSBP;
    }
    currentProcess->context->stackBasePointer = prevSBP;
    return nextProcess->context->stackBasePointer;
}

void initializeProcess(uint64_t* eip)
{
    printString("Initializing Process\n",255,255,255);
    process_t newProcess = malloc(256);
    newProcess->pid = getNewPid();
    newProcess->context->stackBasePointer = malloc(256);
    initialize_stack_frame(eip);
    queueProcess(newProcess);
}

void execute(void* eip)
{
    printString("Tried to initialize process.\n",0,0,0);
    process_t newProcess = (void*)0x1200000;
    newProcess->pid = 2;
    newProcess->context->stackBasePointer = (void*)0x1000000;
    initialize_stack_frame(eip);
    queueProcess(newProcess);
}

void initializeProcessStackFrame(uint64_t* initialEIP)
{
    initialize_stack_frame(initialEIP);
}
