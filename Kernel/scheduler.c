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

uint64_t kernelTableAddress = 0x0; //placeholder
process_t currentProcess = NULL;
pid_t lastPid;

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

void listProcesses(pid_t ** buffer, char ** namesBuffer){
    listQueue(buffer,namesBuffer);
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
    printString("Tried to initialize process.\n",100,200,200);
    printString(nameBuffer,100,200,200);
    printQueue();

    process_t newProcess = malloc(sizeof(struct process_t_CDT));
    //printInt(newProcess, 0,255,0);
    printString("a\n", 255, 255, 255);
    newProcess->pid = 3;
    printString("b\n", 255, 255, 255);
    newProcess->name = malloc(MAX_PROCESS_NAME_LENGTH);
    printString("c\n", 255, 255, 255);
    memcpy(newProcess->name, nameBuffer,strleng(nameBuffer));
    printString("d\n", 255, 255, 255);
    void* sbp = malloc(PROCESS_STACK_SIZE) + PROCESS_STACK_SIZE - sizeof(uint64_t);
    printInt((uint64_t) sbp, 0,255,255);
    printInt((uint64_t) eip, 0,255,255);
    printString("e\n", 255, 255, 255);
    newProcess->context = malloc(sizeof(struct process_context_CDT));
    //printInt((uint64_t) newProcess->context, 255,0,0);
    //printInt((uint64_t) malloc(1), 255,0,0);
    printString("f\n", 255, 255, 255);
    void* temp = initialize_stack_frame(eip, sbp);
    newProcess->context->stackPointer = temp;
    //printInt((uint64_t) temp, 255,255,0);
    //printInt((uint64_t) newProcess->context->stackPointer, 255,0,0);
    printString("g\n",255,255,255);
    if(queueProcess(newProcess)>=0)
        printString("Queued process correctly.\n", 100, 200, 200);
    printQueue();
}
