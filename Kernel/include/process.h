//
// Created by juangod on 15/04/18.
//

#ifndef TP2_TEMPORARY_PROCESS_H
#define TP2_TEMPORARY_PROCESS_H

#include <stdint.h>
#include "lib.h"

struct process_initial_stack{
    uint64_t gs;
    uint64_t fs;
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
};

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
