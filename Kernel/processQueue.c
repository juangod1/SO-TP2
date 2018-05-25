#include "include/processQueue.h"

#define MAX_PROCESSES 256
#define MAX_PROCESS_NAME_LENGTH 20

node first = NULL;
node last = NULL;
int queueSize = 0;

int add(process_t process){
    if(process==NULL)
       return -2;

    node newNode = malloc(sizeof(struct node_CDT));
    if(newNode==NULL) {
        perror("MALLOC RETURNED NULL");
        return -1;
    }

    newNode->process = process;
    newNode->tail = NULL;

    if (queueSize==0){
        first = newNode;
        last = newNode;
        queueSize++;
        return 0;
    }

    last->tail = newNode;
    last = newNode;

    queueSize++;
    return 0;
}


process_t poll(char checkIfWoke){
    if (queueSize==0)
        return NULL;

    char skippedSleepingProcess = 0;
    node tmp = first;
    node previous = NULL;

    if(checkIfWoke){
        while( tmp->process->sleeps ){
            if(tmp->tail == NULL)
                return NULL; // No woke processes

            skippedSleepingProcess = 1;
            previous = tmp;
            tmp = tmp->tail;
        }
    }

    if (queueSize==1){
        first = NULL;
        last = NULL;
        process_t process = tmp->process;
        free(tmp);
        queueSize=0;
        return process;
    }

    if(skippedSleepingProcess) {
        previous->tail = tmp->tail;
        if(tmp->tail == NULL){
            last = previous;
        }
    }
    else
        first = tmp->tail;

    process_t process = tmp->process;
    free(tmp);
    queueSize--;
    return process;
}

void freeNodeMemory(node nodeToFree){
    freeProcessMemory(nodeToFree->process);
    free(nodeToFree);
}

int getQueueSize(){
    return queueSize;
}

process_t peekByPosition(int position){
    if(queueSize==0)
        return NULL;

    if(queueSize<position)
        return NULL;

    node tmp = first;
    int i;

    for(i=0;i<position;i++)
        tmp=tmp->tail;

    return tmp->process;
}

process_t peekByPID(pid_t pid){
    if(queueSize==0)
        return NULL;

    node tmp = first;

    int count=queueSize;
    while(count-- != 0 && tmp->process->pid != pid) {
        if(tmp->tail==NULL)
            return NULL;

        tmp = tmp->tail;
    }

    return tmp->process;
}

void listQueue(pid_t * processesPID, int * processesSleep, char * processesNames, int * processesAmount)
{
    if(queueSize==0)
        return;

    int i;
    node tmp=first;
    for(i=0;i<queueSize;i++) {
        processesPID[i] = tmp->process->pid;
        processesSleep[i] = tmp->process->sleeps;
        memcpy(processesNames,tmp->process->name,strleng(tmp->process->name));
        processesNames+=MAX_PROCESS_NAME_LENGTH;
        tmp = tmp->tail;
    }
    processesAmount[0]=queueSize;
}

void printQueue() { // FOR DEBUGGING
    printInt(queueSize,255,0,0);
    if (queueSize == 0) {
        printString(" ¡QUEUE IS EMPTY! \n",255,255,255);
        return;
    }

    int i;
    node tmp=first;
    printString("PID    SLEEPS    NAME    ADDRESS    TAIL\n",255,255,255);
    for(i=0;i<queueSize;i++) {
        printInt((uint64_t)tmp->process->pid,255,255,255);
        printString("       ",255,255,255);
        printInt((uint64_t)tmp->process->sleeps,255,255,255);
        printString("      ",255,255,255);
        printString(tmp->process->name,255,255,255);
        printString("      ",255,255,255);
        printInt((uint64_t)tmp,255,255,255);
        printString("      ",255,255,255);
        printInt((uint64_t)(tmp->tail),255,255,255);
        printString("\n",255,255,255);

        tmp = tmp->tail;
    }
}

int getInput(pid_t pid)
{
  if(queueSize==0)
      return -1;

  node tmp = first;

  int count=queueSize;
  while(count-- != 0 && tmp->process->pid != pid) {
      if(tmp->tail==NULL)
          return -1;

      tmp = tmp->tail;
  }

  return tmp->process->input;
}

int getOutput(pid_t pid)
{
  if(queueSize==0)
      return -1;

  node tmp = first;

  int count=queueSize;
  while(count-- != 0 && tmp->process->pid != pid) {
      if(tmp->tail==NULL)
          return -1;

      tmp = tmp->tail;
  }

  return tmp->process->output;
}

void destroyQueue(){
    if(queueSize==0)
        return;

    process_t temp;
    while( (temp=poll(0)) != NULL)
        freeProcessMemory(temp);

    first=NULL;
    last=NULL;
    queueSize = 0;
}

void removeLast()
{
    node tmp = first;
    node prev = NULL;
    if(queueSize==0 || tmp == NULL)
        return;
    while(tmp->tail != NULL){
        prev = tmp;
        tmp = tmp->tail;
    }
    prev->tail = NULL;
    --queueSize;
    free(tmp->process);
    free(tmp);
}


int removeByPid(pid_t pid)
{
    node tmp = first;
    node prev = NULL;

    if(queueSize==0 || tmp==NULL)
        return -2;

    int count=queueSize;
    while(count-- != 0 && tmp->process->pid != pid) {
        if(tmp->tail==NULL)
            return -3;

        prev=tmp;
        tmp = tmp->tail;
    }
    if(tmp==NULL)
        return -1;

    prev->tail = tmp->tail;
    if(last->process->pid == tmp->process->pid)
        last = prev;

    free(tmp->process->name);
    free(tmp->process);
    free(tmp);
    queueSize--;

    return 0;
}
