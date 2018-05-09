#ifndef STDLIB_H_
#define STDLIB_H_

#include <stdint.h>
#include <sys/types.h>

typedef struct mbd_t_Struct * mbd_t;
struct mbd_t_Struct
{
  size_t size;
  char block;
  void * key;
};


#define IS_DIGIT(c) ((c - '0') >= 0 && (c - '0') <= 9)
#define DECIMAL_PLACES 4

typedef int pid_t;

//MEMORYMANAGER//
typedef struct dataBlockStruct * dataBlock;
struct dataBlockStruct {
	size_t size;
	dataBlock next;
	int free;
};

#define DBLOCK_SIZE (sizeof(struct dataBlockStruct))
void* sysMalloc(size_t s);
dataBlock expandHeap(dataBlock first, size_t size);
dataBlock searchFreeBlock(dataBlock start, size_t size);
dataBlock searchFreeBlock(dataBlock start, size_t size);
dataBlock getLastDataBlock(dataBlock first);
//------------//

void reset(char * string, int size);
int strleng(const char* s);
void sysPrintString(char * string, int R, int G, int B);
void sysPrintInt(int num, int B, int G, int R);
void sysPrintFloat(float num, int B, int G, int R);
void sysGetTime(int * buffer);
void sysNewLine();
void sysReadInput(char * buffer);
void sysClear();
void * memcpy(void * destination, const void * source, uint64_t length);
int countDigits(int num);
void sysPaintPixel(int x, int y, char R, char G, char B);
void sysGetChar(char * ch);
void copy(char* copy, char* original, int len);
int subStrleng(const char * s, const char c);
void sysPrintFloat(float num, int B, int G, int R);
int getPid();
void sysExecute(void* functionPointer, char * name);
void sysTestSuite(int num);
void sysCSD();
void sysGetProcesses(pid_t * processesPID, int * processesSleep, char * processesNames, int * processesAmount);
int checkIfForeground();
void semStop(int key);
void semStart(int key, int value);
void semSignal(int key);
void semWait(int key);
void finalizeMessageBox(mbd_t descriptor);
void recieveMessage(mbd_t descriptor, void * buffer);
void sendMessage(mbd_t descriptor, void * messageContent);
void sysExit();
#endif
