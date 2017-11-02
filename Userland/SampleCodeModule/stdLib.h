#ifndef IDTLOADER_H_
#define IDTLOADER_H_

#include <stdint.h>

void sysPrintString(uint8_t color, char * string);
void sysPrintInt(uint8_t color, int num);
void sysGetTime(int * buffer);
void sysNewLine();
void sysReadInput(char * buffer);
void sysClear();

#endif
