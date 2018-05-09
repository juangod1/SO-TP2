//
// Created by juangod on 15/04/18.
//

#ifndef TP2_TEMPORARY_PROCESSQUEUE_H
#define TP2_TEMPORARY_PROCESSQUEUE_H

#include "process.h"

typedef struct node_CDT * node;
struct node_CDT {
    node tail;
    process_t process;
};

int add(process_t process);
int getQueueSize();
process_t poll(char checkIfWoke);
void freeNodeMemory(node nodeToFree);
process_t peekByPosition(int position);
process_t peekByPID(pid_t pid);
void listQueue();
void destroyQueue();
void printQueue();
void listQueue(pid_t * processesPID, int * processesSleep, char * processesNames, int * processesAmount);
#endif //TP2_TEMPORARY_PROCESSQUEUE_H
