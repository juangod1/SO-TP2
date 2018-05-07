//
// Created by juangod on 18/04/18.
//
#include "include/process.h"
#include "include/memorymanager.h"
#include "include/processQueue.h"
#include "include/videoDriver.h"
#include "scheduler.h"

void* initialize_stack_frame(void* rip, void* rbp);
uint64_t* get_eip();

process_t currentProcess = NULL;
pid_t lastPid=-1;

pid_t getPid(){
    if(currentProcess == NULL)
        return -1;
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

void listProcesses(pid_t ** buffer, char ** namesBuffer, int processNum[1]){
    listQueue(buffer,namesBuffer,processNum);
}

int queueProcess(process_t process){
    int ret = add(process);
    //printString("cualquier cosa\n",255,0,0);
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

void debug()
{
    printString("asdsdsa", 0,0,255);
}

void * schedule(void* prevSP)
{
    /*printString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n",255,0,0);
    uint64_t * curr = (uint64_t *)prevSP;
    printInt(curr, 0,255,0);
    printString("\n",255,0,0);
    for(uint64_t i = 0; i < 30; i++){
        printInt(curr[i], 255,255,255);
        printString("\n",255,0,0);
    }
    printString("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n",255,0,0);
    
        while(1);*/
    process_t prevProcess = getCurrentProcess();
    process_t nextProcess = getNextProcess();
    

    if(nextProcess == NULL) // QUEUE IS EMPTY
    {
        return prevSP;
    }
    if(prevProcess == NULL) // FIRST PROCESS CASE
    {
        //printString("load first\n",255,0,0);
        queueProcess(nextProcess);
        //printString("dequeued succ\n",255,0,0);
        /*uint64_t * curr = (uint64_t *)nextProcess->context->stackPointer;
        printInt(curr, 0,255,0);
        printString("\n",255,0,0);
        printInt(nextProcess, 0,255,0);
        printString("\n",255,0,0);
        printInt(nextProcess->context, 0,255,0);
        printString("\n",255,0,0);
        for(uint64_t i = 0; i < 30; i++){
            printInt(curr[i], 255,255,255);
            printString("\n",255,0,0);
        }*/
        return nextProcess->context->stackPointer;
    }
    else
    {
        //printString("ignore sched\n",255,0,0);
        //return prevSP;
        prevProcess->context->stackPointer = prevSP;
        queueProcess(nextProcess);
        return nextProcess->context->stackPointer;
    }
}

void execute(void* eip, char * nameBuffer)
{
    printString("Initializing process ",100,200,200);
    printString(nameBuffer,100,200,200);
    printString("\n",0,0,0);

    process_t newProcess = malloc(sizeof(struct process_t_CDT));
    newProcess->pid = getNewPid();
    newProcess->name = malloc(MAX_PROCESS_NAME_LENGTH);
    memcpy(newProcess->name, nameBuffer,strleng(nameBuffer));
    void* sbp = malloc(PROCESS_STACK_SIZE) + PROCESS_STACK_SIZE - sizeof(uint64_t);
    newProcess->context = malloc(sizeof(struct process_context_CDT));
    void* temp = initialize_stack_frame(eip, sbp);
    newProcess->context->stackPointer = temp;
    if(queueProcess(newProcess)<0)
        perror("Process queueing error.");

    printString("Process list:\n",200,200,10);
    printQueue();
}
