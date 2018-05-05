//
// Created by juangod on 15/04/18.
//
#include "include/process.h"
#include "include/memorymanager.h"

void freeProcessMemory(process_t process) {
    free(process->context);
    free(process);
}
