//
// Created by juangod on 18/04/18.
//

#ifndef TP2_TEMPORARY_SCHEDULER_H
#define TP2_TEMPORARY_SCHEDULER_H

#include "process.h"

#define MAX_PROCESS_NAME_LENGTH 20
#define PROCESS_STACK_SIZE 2048

pid_t getPid();
process_t getCurrentProcess();
int sleepProcess(pid_t pid);
int wakeProcess(pid_t pid);
process_t getNextProcess();
int queueProcess(process_t process);
void destroyProcessQueue();
int getAmountOfProcesses();
void listProcesses();
void execute(void* eip, char* nameBuffer, int * pid);
#endif //TP2_TEMPORARY_SCHEDULER_H
