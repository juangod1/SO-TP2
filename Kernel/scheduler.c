//
// Created by juangod on 18/04/18.
//
#include "include/process.h"
#include "include/memorymanager.h"
#include "include/processQueue.h"
#include "include/videoDriver.h"
#include "scheduler.h"
#include "include/debugging.h"

void* initialize_stack_frame(void* rip, void* rbp);
uint64_t* get_eip();
void clear_interrupts();
void set_interrupts();

process_t currentProcess = NULL;
pid_t lastPid=-1;

int halt = 0;

pid_t getPid(){
    if(currentProcess == NULL)
        return -1;
    return currentProcess->pid;
}

process_t getCurrentProcess(){
    return currentProcess;
}

void spoof_tick();

// Returns -1 if PID not found, 0 if slept, 1 if already sleeping
int sleepProcess(pid_t pid){
    process_t find = peekByPID(pid);
    if (find==NULL)
        return -1;

    if(find->sleeps)
        return 1;

    find->sleeps = 1;

    spoof_tick();
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

void listProcesses(pid_t * processesPID, int * processesSleep, char ** processesNames, int * processesAmount){
    listQueue(processesPID,processesSleep,processesNames,processesAmount);
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

void * schedule(void* prevSP)
{
    halt = 0;
    process_t prevProcess = getCurrentProcess();
    process_t nextProcess = getNextProcess();

    if(nextProcess == NULL) // QUEUE IS EMPTY
    {
        return prevSP;
    }
    queueProcess(nextProcess);
    if(prevProcess == NULL) // FIRST PROCESS CASE
    {
        return nextProcess->stackPointer;
    }
    else
    {
        prevProcess->stackPointer = prevSP;
        return nextProcess->stackPointer;
    }
}

void execute(void* eip, char * nameBuffer, int * pid)
{
    printString("d1",255,0,0);
    process_t newProcess = malloc(sizeof(struct process_t_CDT));
    printString("d2",255,0,0);
    if(newProcess == NULL){
        printString("Not enough memory for process.\n", 0, 0, 255);
    }
    printString("d3",255,0,0);
    newProcess->pid = getNewPid();
    printString("d4",255,0,0);
    newProcess->name = malloc(MAX_PROCESS_NAME_LENGTH);
    printString("d5",255,0,0);
    if(newProcess->name == NULL){
        printString("Not enough memory for process.\n", 0, 0, 255);
        free(newProcess);
    }
    printString("d6",255,0,0);
    memcpy(newProcess->name, nameBuffer,strleng(nameBuffer));
    printString("d7",255,0,0);
    void* sp = getStack(newProcess->pid);
    if(sp == NULL){
        printString("Not enough memory for process.\n", 0, 0, 255);
        free(newProcess);
    }
    printString("d8",255,0,0);
    void* temp = initialize_stack_frame(eip, sp);
    printString("d9",255,0,0);
    newProcess->stackPointer = temp;
    printString("d10",255,0,0);
    queueProcess(newProcess);
    printString("d11",255,0,0);
    *pid = newProcess->pid;
    printQueue();
}

void exit()
{
    printQueue();
    pid_t pid = getPid();
    removeByPid(pid);
    dropBookPageForProcess(pid);
    printQueue();
}
