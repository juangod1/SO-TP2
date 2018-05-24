#ifndef PIPE_H
#define PIPE_H

#include <stdio.h>
#include <stdlib.h>

#define PIPESIZE 100

typedef struct pipe_CDT * pipe;
struct pipe_CDT {
    char readIndex;
    char writeIndex;
    char count;
    char * buffer;
};

void initializePipe(pipe * p);
void finalizePipe(pipe * p);
void read(pipe * p, char * c);
void write(pipe * p, char c);

#endif
