//
// Created by juangod on 15/04/18.
//

#ifndef TP2_TEMPORARY_PROCESS_H
#define TP2_TEMPORARY_PROCESS_H

#include <stdint.h>
#include "lib.h"

typedef struct process_context_CDT * process_context;
struct process_context_CDT {
    void* stackPointer;
    // registros etc
};

typedef struct process_t_CDT * process_t;
struct process_t_CDT {
    pid_t pid;
    char sleeps;
    char * name;
    process_context context;
};

void freeProcessMemory(process_t process);

#endif //TP2_TEMPORARY_PROCESS_H
