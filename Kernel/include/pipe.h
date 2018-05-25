#ifndef PIPE_H
#define PIPE_H

#include "lib.h"
#include "memorymanager.h"

#define PIPESIZE 100

typedef struct pipe_CDT * pipe;
struct pipe_CDT {
    char readIndex;
    char writeIndex;
    char count;
    char * buffer;
    pid_t blocked;
};

void initializePipe(pipe * p);
void finalizePipe(pipe * p);
void read(pipe * p, char * c);
void write(pipe * p, char c);

#endif
