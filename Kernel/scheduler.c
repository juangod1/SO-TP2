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
    printString("Queue before sleep:\n",255,255,255);
    printQueue();
    process_t find = peekByPID(pid);
    if (find==NULL)
        return -1;

    if(find->sleeps)
        return 1;
    find->sleeps = 1;
    printString("Queue after sleep:\n",255,255,255);
    printQueue();
    return 0;
}

// Returns -1 if PID not found, 0 if woke up, 1 if already woke
int wakeProcess(pid_t pid){
    printString("Queue before woke:\n",255,255,255);
    printQueue();
    process_t find = peekByPID(pid);
    if (find==NULL)
        return -1;

    if(!find->sleeps)
        return 1;

    find->sleeps = 0;
    printString("Queue after woke:\n",255,255,255);
    printQueue();
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
        //printString("nextProcess is null\n",255,0,0);
        return prevSP;
    }
    queueProcess(nextProcess);
    if(prevProcess == NULL) // FIRST PROCESS CASE
    {
        //printString("prevProcess is null but next process is not null\n",255,0,0);
        //printString("NextProcess name: ", 0, 255, 0);
        //printString(nextProcess->name, 0, 255, 0);
        //printString("\n", 0, 0, 0);
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
        //printString("NextProcess name: ",0,255,0);
        //printString(nextProcess->name,0,255,0);
        //printString("\n",0,0,0);
        return nextProcess->stackPointer;
    }
}

void execute(void* eip, char * nameBuffer)
{
    printString("Tried to initialize process: ",100,200,200);
    printString(nameBuffer,100,200,200);
    printString("\n",0,0,0);

    printString("QueueSize before exec:",0,255,0);
    printInt(getQueueSize(),0,255,0);
    printString("\n",0,0,0);
    //printQueue();
    printString("a1\n",0,0,255);
    process_t newProcess = malloc(sizeof(struct process_t_CDT));
    if(newProcess == NULL){
        printString("No space for process.\n", 0, 0, 255);
    }
    printString("a2\n",0,0,255);
    newProcess->pid = getNewPid();
    printString("a3\n",0,0,255);
    newProcess->name = malloc(MAX_PROCESS_NAME_LENGTH);
    printString("a4\n",0,0,255);
    if(newProcess->name == NULL){
        printString("No space for process.\n", 0, 0, 255);
        free(newProcess);
    }
    printString("a5\n",0,0,255);
    memcpy(newProcess->name, nameBuffer,strleng(nameBuffer));
    void* sp = getStack(newProcess->pid);
    //void* sp = malloc(PROCESS_STACK_SIZE) + PROCESS_STACK_SIZE - sizeof(uint64_t);
    if(sp == NULL){
        printString("No space for process.\n", 0, 0, 255);
        free(newProcess);
    }
    printString("a6\n",0,0,255);
    void* temp = initialize_stack_frame(eip, sp);
    newProcess->stackPointer = temp;
    if(queueProcess(newProcess)>=0)
        printString("Queued process correctly.\n", 100, 200, 200);
    else{
        printString("Cannot quque process, not enough memory",0,0,255);
    }
    printString("This is the state of the queue: \n",255,255,255);
    printQueue();
    printString("QueueSize after exec:",0,255,0);
    printInt(getQueueSize(),0,255,0);
    printString("lalalal",0,0,255);
    printString("\n",0,0,0);
}

void exit()
{
    printString("Queue before exit:\n",255,255,255);
    printQueue();
    removeLast();
    printString("Queue after exit:\n",255,255,255);
    printQueue();
}
