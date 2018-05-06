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
  return 1;//getForegroundPID()==getPid();
}

void sysWriteChar(char ch, unsigned char color_blue, unsigned char color_green, unsigned char color_red) {
  if(checkIfForeground())
    sysCall(4,ch,color_blue,color_green,color_red,0);
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
  sysCall(2,(uint64_t)ch,0,0,0,0);
}

void sysTestSuite(int num){
    sysCall(6,num,0,0,0,0);
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
  sysPrintString("Entered sysExecute\n",0,0,0);
  sysCall(7,(uint64_t)functionPointer,name,0,0,0);
}

int getPid()
{
  int pid;
  sysCall(8,(uint64_t)&pid,0,0,0,0);
  return pid;
}

void sysGetProcesses(pid_t ** buffer, char ** namesBuffer){
  sysCall(9,buffer,namesBuffer,0,0,0);
}

void sendMessage(mbd_t descriptor, void * messageContent)
{
  sysCall(10,descriptor,messageContent,0,0,0);
}

void recieveMessage(mbd_t descriptor, void * buffer)
{
  sysCall(11,descriptor,buffer,0,0,0);
}

void finalizeMessageBox(mbd_t descriptor)
{
  sysCall(12,descriptor,0,0,0,0);
}

void semWait(int key)
{
  sysCall(13,key,0,0,0,0);
}

void semSignal(int key)
{
  sysCall(14,key,0,0,0,0);
}

void semStart(int key, int value)
{
  sysCall(15,key,value,0,0,0);
}

void semStop(int key)
{
  sysCall(16,key,0,0,0,0);
}


void listProcesses(){
  int buffer[MAX_PROCESSES][2]={};
  int names[MAX_PROCESSES][MAX_PROCESS_NAME_LENGTH]={};
  sysGetProcesses(buffer,names);

  sysPrintString("PID    NAME        SLEEPS\n",255,255,255);
  int i;
  for(i=0;i<MAX_PROCESSES;i++){
    sysPrintInt(buffer[i][0],255,255,255);
    sysPrintString("            ",255,255,255);
    sysPrintString(names[i],255,255,255);
    sysPrintString("            ",255,255,255);
    sysPrintInt(buffer[i][1],255,255,255);
    sysPrintString("\n",0,0,0);
  }
}
