//
// Created by juangod on 15/04/18.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "processQueue.h"

node first = NULL;
node last = NULL;
int queueSize = 0;

int add(process_t process){
    if(process==NULL)
       return -2;

    node newNode = malloc(sizeof(struct node_CDT));
    if(newNode==NULL) {
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

    if(skippedSleepingProcess)
        previous->tail = tmp->tail;
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
    while(tmp->process->pid != pid) {
        if(tmp->tail==NULL)
            return NULL;

        tmp = tmp->tail;
    }

    return tmp->process;
}

void listQueue(){
    if(queueSize==0){
        printf("Queue is empty.\n");
        return;
    }

    int i;
    node tmp=first;
    printf("POSITION    PID    SLEEP\n");
    for(i=0;i<queueSize;i++) {
        printf("%d           %d          %d \n",i+1,tmp->process->pid,tmp->process->sleeps);
        tmp = tmp->tail;
    }
}

void destroyQueue(){
    int i;
    if(queueSize==0)
        return;

    process_t temp;
    for(i=0;i<queueSize;i++){
        temp = poll(0);
        freeProcessMemory(temp);
    }
    first=NULL;
    last=NULL;
    queueSize = 0;
}