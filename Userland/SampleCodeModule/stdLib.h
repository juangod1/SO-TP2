#ifndef IDTLOADER_H_
#define IDTLOADER_H_

#include <stdint.h>

void sysPrintString(char * string, int R, int G, int B);
void sysPrintInt(int num, int R, int G, int B);
void sysGetTime(int * buffer);
void sysNewLine();
void sysReadInput(char * buffer);
void sysClear();

#endif
