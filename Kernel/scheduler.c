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
    process_t prevProcess = getCurrentProcess();
    process_t nextProcess = getNextProcess();
    
    //dumpStackAndHalt(prevSP + sizeof(uint64_t));
    //processorWait(10000000);

    if(nextProcess == NULL) // QUEUE IS EMPTY
    {
        printString("nextProcess is null\n",255,0,0);
        return prevSP;
    }
    if(prevProcess == NULL) // FIRST PROCESS CASE
    {
        printString("prevProcess is null but next process is not null\n",255,0,0);
        queueProcess(nextProcess);
        printString("NextProcess name: ", 0, 255, 0);
        printString(nextProcess->name, 0, 255, 0);
        printString("\n", 0, 0, 0);
        return nextProcess->stackPointer;
    }
    else
    {
        // printString("Prev and next processes are not null.\n",255,0,0);
        // printString("PrevProcess name: ",0,255,0);
        // printString(prevProcess->name,0,255,0);
        // printString("\n",0,0,0);
        // printString("NextProcess name: ",0,255,0);
        // printString(nextProcess->name,0,255,0);
        // printString("\n",0,0,0);
        prevProcess->stackPointer = prevSP;
        queueProcess(nextProcess);
        printString("NextProcess name: ",0,255,0);
        printString(nextProcess->name,0,255,0);
        printString("\n",0,0,0);
        return nextProcess->stackPointer;
    }
}

void execute(void* eip, char * nameBuffer)
{
    printString("Tried to initialize process: ",100,200,200);
    printString(nameBuffer,100,200,200);
    printString("\n",0,0,0);
    //printQueue();

    process_t newProcess = malloc(sizeof(struct process_t_CDT));
    if(newProcess == NULL){
        printString("No space for process.\n", 0, 0, 255);
    }
    newProcess->pid = 3;
    newProcess->name = malloc(MAX_PROCESS_NAME_LENGTH);
    if(newProcess->name == NULL){
        printString("No space for process.\n", 0, 0, 255);
        free(newProcess);
    }
    memcpy(newProcess->name, nameBuffer,strleng(nameBuffer));
    void* sp = malloc(PROCESS_STACK_SIZE) + PROCESS_STACK_SIZE - sizeof(uint64_t);
    if(sp == NULL){
        printString("No space for process.\n", 0, 0, 255);
        free(newProcess);   
    }
    void* temp = initialize_stack_frame(eip, sp);
    newProcess->stackPointer = temp;
    if(queueProcess(newProcess)>=0)
        printString("Queued process correctly.\n", 100, 200, 200);
    else{
        printString("Cannot quque process, not enough memory",0,0,255);
    }
    printString("This is the state of the queue: \n",255,255,255);
    printQueue();
}
