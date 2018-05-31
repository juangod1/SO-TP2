#include "scheduler.h"
#include "memorymanager.h"

void* initialize_stack_frame(void* rip, void* rbp);
uint64_t* get_eip();
void clear_interrupts();
void set_interrupts();
void idleProgram();
process_t executeIdle();

process_t currentProcess = NULL;
process_t idleProcess = NULL;
pid_t lastPid=-1;

int setupComplete = 0;

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

    if(find->sleeps) {
        return 1;
    }

    printString("Slept",255,255,255);
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
    process_t nextPeek = peekByPosition(0);
    if(nextPeek == NULL){
        return NULL;
    }
    process_t next = poll(1);
    if(next == NULL){
        if(idleProcess == NULL){
            idleProcess = executeIdle();
            next = idleProcess;
        }
        next = idleProcess;
    }
//
//    if(next != NULL){
//        setupComplete = 1;
//
//        if(idleProcess == NULL)
//            idleProcess = executeIdle();
//    }
//
//    if(setupComplete) {
//        if (next == NULL && peekByPID(idleProcess->pid) == NULL && nextPeek->sleeps) {
//            queueProcess(idleProcess);
//            next = poll(1);
//            queueProcess(idleProcess);
//        }
//        if (next != NULL && next->pid != idleProcess->pid) {
//            removeByPid(idleProcess->pid);
//        }
//    }
//    currentProcess = next;
//    return next;
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
    printQueue();
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
    process_t newProcess = malloc(sizeof(struct process_t_CDT));
    if(newProcess == NULL){
        printString("Not enough memory for process.\n", 0, 0, 255);
    }
    newProcess->pid = getNewPid();
    newProcess->name = malloc(MAX_PROCESS_NAME_LENGTH);
    if(newProcess->name == NULL){
        printString("Not enough memory for process.\n", 0, 0, 255);
        free(newProcess);
    }
    memcpy(newProcess->name, nameBuffer,strleng(nameBuffer));
    void* sp = getStack(newProcess->pid);
    if(sp == NULL){
        printString("Not enough memory for process.\n", 0, 0, 255);
        free(newProcess);
    }
    void* temp = initialize_stack_frame(eip, sp);
    newProcess->stackPointer = temp;
    newProcess->input = 0;
    newProcess->output = 0;
    queueProcess(newProcess);
    *pid = newProcess->pid;
}

void exit()
{
    pid_t pid = getPid();
    removeByPid(pid);
    dropBookPageForProcess(pid);
    spoof_tick();
 }

 void kill(pid_t pid)
 {
     removeByPid(pid);
     dropBookPageForProcess(pid);
     spoof_tick();
 }

 void idleProgram()
 {
     while(1);
 }

 process_t executeIdle()
 {
     process_t newProcess = malloc(sizeof(struct process_t_CDT));
     if(newProcess == NULL){
         printString("Not enough memory for process.\n", 0, 0, 255);
     }
     newProcess->pid = getNewPid();
     newProcess->name = malloc(MAX_PROCESS_NAME_LENGTH);
     if(newProcess->name == NULL){
         printString("Not enough memory for process.\n", 0, 0, 255);
         free(newProcess);
     }
     memcpy(newProcess->name, "idle",strleng("idle"));
     void* sp = getStack(newProcess->pid);
     if(sp == NULL){
         printString("Not enough memory for process.\n", 0, 0, 255);
         free(newProcess);
     }
     void* temp = initialize_stack_frame(idleProgram, sp);
     newProcess->stackPointer = temp;
     newProcess->input = 0;
     newProcess->output = 0;
     return newProcess;
 }