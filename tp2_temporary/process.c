//
// Created by juangod on 15/04/18.
//
#include <stdlib.h>
#include "process.h"

void freeProcessMemory(process_t process) {
    free(process->context);
    free(process);
}
