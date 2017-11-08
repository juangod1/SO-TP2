#include "stdLib.h"
#include "mathLib.h"
#include <stdint.h>
#define MAX_DIGITS 20

extern int sysCall(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

void reset(char * string, int size){
  for (int i = 0; i < size; i++){
    *(string + i)=0;
  }
}


void sysWriteChar(char * ch, unsigned char color_blue, unsigned char color_green, unsigned char color_red) {
  sysCall(7,ch,color_blue,color_green,color_red,0);
}

void sysPrintString(char * string, int B, int G, int R){
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

  while (*(s + i) != c) {
    i++;
  }

  return i;
}

int strleng(const char* s){
	return subStrleng(s, '\0');
}

void sysPrintInt(int num, int B, int G, int R) {
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
  sysPrintInt((int)num, B, G, R);

  if (num != 0) {
    sysPrintString(".", B, G, R);
  }

  while (num != 0) {
    num -= (int)num;
    num *= 10;
    sysPrintInt((int)num, B, G, R);
  }
}

int countDigits(int num){
	int dig = 1;
	while((num/=10) != 0) dig++;
	return dig;
}
void sysGetChar(char * ch){
  sysCall(4,ch,0,0,0,0);
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

void sysPaintPixel(int x, int y, char B, char G, char R) {
  sysCall(8, x, y, B, G, R);
}
