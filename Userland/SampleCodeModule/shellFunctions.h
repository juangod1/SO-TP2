#ifndef SHELLFUNCTIONS_H
#define SHELLFUNCTIONS_H

#include "stdLib.h"
#include "shell.h"


int calculateWrapper(int words, char * input1, char * input2,char * input3);
int calculateVerifications(int words, char* input1, char* input2, char* input3);
int calculate(char* func, int param1, int param2);
int displayTime();
int help(int words, char ** input);
int verifyOperation(char * op);
int echo(char ** input, int words);
int setFontColor(char * input, int * blue, int * green, int * red);
int clear(int words);;
int graph(char * input1, char* input2, char * input3);

#endif
