#include "stdLib.h"
#include <stdint.h>
#define MAX_DIGITS 20

extern int sysCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

void sysPrintString(char * string, int R, int G, int B){
  int len = strleng(string);
  int i;
  for(i=0;i<len;i++){
    sysWriteChar(string[i]);
  }
}
int strleng(const char *str){
	int i=0;
	while(*(str+i)) i++;
	return i;
}

void sysPrintInt(int num, int R, int G, int B){
  int dig = countDigits(num);
  char numbers[MAX_DIGITS] = {};
  int count=0;

  while(count!=dig){
    numbers[dig-1-count++]=num%10+48;
    num /= 10;
  }

  numbers[dig]='\0';

  if (num<0)
    sysWriteChar('-');

  sysPrintString(numbers,R,G,B);
}
int countDigits(int num){
	int dig = 1;
	while((num/=10) != 0) dig++;
	return dig;
}
void sysGetChar(char * ch){
  sysCall(4,ch,0,0,0,0);
}
void sysReadInput(char * buffer){
  sysCall(5,buffer,0,0,0,0);
}
void sysWriteChar(char * ch){
  sysCall(7,ch,0,0,0,0);
}


void sysGetTime(int * buffer){
	buffer[0] = sysCall(3,0,0,0,0,0); // Seconds
	buffer[1] = sysCall(3,2,0,0,0,0); // Minutes
	buffer[2] = sysCall(3,4,0,0,0,0); // Hours
	buffer[3] = sysCall(3,7,0,0,0,0); // Day
	buffer[4] = sysCall(3,8,0,0,0,0); // Month
	buffer[5] = sysCall(3,9,0,0,0,0); // Year
}

void sysClear(){
	sysCall(6,0,0,0,0,0);
}
