#include "stdLib.h"
#include "mathLib.h"
#include "contextSwitchDemo.h"
#include <stdint.h>
#include <sys/types.h>
#include "shell.h"
#define MAX_DIGITS 20

extern int sysCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

void reset(char * string, int size){
  for (int i = 0; i < size; i++){
    *(string + i)=0;
  }
}


int checkIfForeground(){
  return (getForegroundPID()==getPid()?1:0);
}

void sysWriteChar(char ch, unsigned char color_blue, unsigned char color_green, unsigned char color_red) {
    sysCall(4, ch, color_blue, color_green, color_red, 0);
}

void DEBUGWriteChar(char ch, unsigned char color_blue, unsigned char color_green, unsigned char color_red) {
        sysCall(4, ch, color_blue, color_green, color_red, 0);

}

void DEBUGPrintString(char * string, int B, int G, int R){
    int len = strleng(string);
    int i;
    for(i=0;i<len;i++){
        DEBUGWriteChar(string[i], B, G, R);
    }
}

void sysPrintString(char * string, int B, int G, int R){
  if(!checkIfForeground())
    return;

  int len = strleng(string);
  int i;
  for(i=0;i<len;i++){
    sysWriteChar(string[i], B, G, R);
  }
}

void copy(char* copy, char* original, int len){
  for(int i=0; i<len; i++){
    *(copy+i)=*(original+i);
  }
}

int subStrleng(const char * s, const char c) {
  int i = 0;

  while (*(s + i) != c && *(s+i)!=0) {
    i++;
  }

  return i;
}

int strleng(const char* s){
	return subStrleng(s, '\0');
}

void sysPrintInt(int num, int B, int G, int R) {
  if(!checkIfForeground())
    return;

  int dig = countDigits(num);
  char numbers[MAX_DIGITS] = {};
  int count = 0;
  int remainder;

  if (num < 0) {
    sysWriteChar('-', B, G, R);
  }

  while (count != dig) {
    remainder = absInt(num % 10);
    numbers[dig - 1 - count++] = remainder + 48;
    num /= 10;
  }

  numbers[dig] = '\0';

  sysPrintString(numbers, B, G, R);
}

void DEBUGPrintInt(int num, int B, int G, int R) {
    int dig = countDigits(num);
    char numbers[MAX_DIGITS] = {};
    int count = 0;
    int remainder;

    if (num < 0) {
        sysWriteChar('-', B, G, R);
    }

    while (count != dig) {
        remainder = absInt(num % 10);
        numbers[dig - 1 - count++] = remainder + 48;
        num /= 10;
    }

    numbers[dig] = '\0';

    sysPrintString(numbers, B, G, R);
}

void sysPrintFloat(float num, int B, int G, int R) {
  if(!checkIfForeground())
    return;

  sysPrintInt((int)num, B, G, R);
  num -= (int)num;
  int aux;
  sysPrintString(".", B, G, R);
  for(int i=1; i<DECIMAL_PLACES; i++){
    aux = num*tenPow(i);
    aux = aux%10;
    aux = aux < 0 ? -aux : aux;
    sysPrintInt((int)aux, B, G, R);
  }
}

int countDigits(int num){
	int dig = 1;
	while((num/=10) != 0) dig++;
	return dig;
}

void sysGetChar(char * ch){
    if(checkIfForeground())
  sysCall(2,(uint64_t)ch,0,0,0,0);
}

void sysExit(){
    sysCall(18,0,0,0,0,0);
}

void sysTestSuite(int num){
    sysCall(6,(uint64_t)num,0,0,0,0);
}

void sysGetTime(int * buffer){
	buffer[0] = sysCall(1,0,0,0,0,0); // Seconds
	buffer[1] = sysCall(1,2,0,0,0,0); // Minutes
	buffer[2] = sysCall(1,4,0,0,0,0); // Hours
	buffer[3] = sysCall(1,7,0,0,0,0); // Day
	buffer[4] = sysCall(1,8,0,0,0,0); // Month
	buffer[5] = sysCall(1,9,0,0,0,0); // Year
}

void sysClear(){
	sysCall(3,0,0,0,0,0);
}

void sysPaintPixel(int x, int y, char B, char G, char R) {
  if(checkIfForeground())
    sysCall(5, x, y, B, G, R);
}

void sysExecute(void* functionPointer, char* name)
{
  sysCall(7,(uint64_t)functionPointer,(uint64_t)name,0,0,0);
}

int getPid()
{
  int pid;
  sysCall(8,(uint64_t)&pid,0,0,0,0);
  return pid;
}

void sysGetProcesses(pid_t ** buffer, char ** namesBuffer, int amount[1]){
  sysCall(9,(uint64_t)buffer,(uint64_t)namesBuffer,amount,0,0);
}

void sysMalloc(void ** buff, size_t size){
    sysCall(17,buff,size,0,0,0);
}

void sendMessage(mbd_t descriptor, void * messageContent)
{
  sysCall(10,(uint64_t)descriptor,(uint64_t)messageContent,0,0,0);
}

void recieveMessage(mbd_t descriptor, void * buffer)
{
  sysCall((uint64_t)11,(uint64_t)descriptor,(uint64_t)buffer,0,0,0);
}

void finalizeMessageBox(mbd_t descriptor)
{
  sysCall((uint64_t)12,(uint64_t)descriptor,0,0,0,0);
}

void semWait(int key)
{
  sysCall((uint64_t)13,(uint64_t)key,0,0,0,0);
}

void semSignal(int key)
{
  sysCall((uint64_t)14,(uint64_t)key,0,0,0,0);
}

void semStart(int key, int value)
{
  sysCall((uint64_t)15,(uint64_t)key,(uint64_t)value,0,0,0);
}

void semStop(int key)
{
  sysCall((uint64_t)16,(uint64_t)key,0,0,0,0);
}

void * memcpy(void * destination, const void * source, uint64_t length)
{
    /*
    * memcpy does not support overlapping buffers, so always do it
    * forwards. (Don't change this without adjusting memmove.)
    *
    * For speedy copying, optimize the common case where both pointers
    * and the length are word-aligned, and copy word-at-a-time instead
    * of byte-at-a-time. Otherwise, copy by bytes.
    *
    * The alignment logic below should be portable. We rely on
    * the compiler to be reasonably intelligent about optimizing
    * the divides and modulos out. Fortunately, it is.
    */
    uint64_t i;

    if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
        (uint64_t)source % sizeof(uint32_t) == 0 &&
        length % sizeof(uint32_t) == 0)
    {
        uint32_t *d = (uint32_t *) destination;
        const uint32_t *s = (const uint32_t *)source;

        for (i = 0; i < length / sizeof(uint32_t); i++)
            d[i] = s[i];
    }
    else
    {
        uint8_t * d = (uint8_t*)destination;
        const uint8_t * s = (const uint8_t*)source;

        for (i = 0; i < length; i++)
            d[i] = s[i];
    }

    return destination;
}

