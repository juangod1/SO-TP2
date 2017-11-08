#ifndef STDLIB_H_
#define STDLIB_H_

#include <stdint.h>

#define IS_DIGIT(c) ((c - '0') >= 0 && (c - '0') <= 9)

void sysPrintString(char * string, int R, int G, int B);
void sysPrintInt(int num, int R, int G, int B);
void sysGetTime(int * buffer);
void sysNewLine();
void sysReadInput(char * buffer);
void sysClear();
void sysPaintPixel(int x, int y, char R, char G, char B);
void sysWriteChar(char ch, unsigned char color_blue, unsigned char color_green, unsigned char color_red);

#endif
