#ifndef STDLIB_H_
#define STDLIB_H_

#include <stdint.h>
#include <sys/types.h>

typedef struct mbd_t_Struct * mbd_t;
struct mbd_t_Struct
{
  size_t size;
  void * key;
};


#define IS_DIGIT(c) ((c - '0') >= 0 && (c - '0') <= 9)
#define DECIMAL_PLACES 4

typedef int pid_t;

void reset(char * string, int size);
int strleng(const char* s);
void sysPrintString(char * string, int R, int G, int B);
void sysPrintInt(int num, int B, int G, int R);
void sysPrintFloat(float num, int B, int G, int R);
void sysGetTime(int * buffer);
void sysNewLine();
void sysReadInput(char * buffer);
void sysClear();
int countDigits(int num);
void sysPaintPixel(int x, int y, char R, char G, char B);
void sysWriteChar(char ch, unsigned char color_blue, unsigned char color_green, unsigned char color_red);
void sysGetChar(char * ch);
void copy(char* copy, char* original, int len);
int subStrleng(const char * s, const char c);
void sysPrintFloat(float num, int B, int G, int R);
int getPid();
void sysExecute(void* functionPointer);
void sysTestSuite(int num);
void sysCSD();
void sysGetProcesses(pid_t ** buffer, char ** namesBuffer);
#endif
