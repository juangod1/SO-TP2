#include <stdint.h>
#include "videoDriver.h"

static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;

void printString(uint8_t color, const char* string){
	int len = strleng(string);
	int i;
	for(i=0;i<len;i++){
		printChar(color,string[i]);
	}
}

void printChar(uint8_t color, char ch){
	*currentVideo = ch;
	*(currentVideo+1) = color;
	currentVideo=currentVideo+2;
}

int countDigits(int num){
	int dig = 1;
	while((num/=10) != 0) dig++;
	return dig;
}

void printInt(uint8_t color, int num){
		int dig = countDigits(num);
		char numbers[MAX_DIGITS] = {};
		int count=0;

		while(count!=dig){
			numbers[dig-1-count++]=num%10+48;
			num /= 10;
		}

		numbers[dig]='\0';

		if (num<0)
			printChar(color,'-');

		printString(color,numbers);
}

void clearScreen(){
	int i;
	for(i=0; i<SCREEN_WIDTH*SCREEN_HEIGHT*2; i++){
		*(video+i) = 0;
	}
}

int strleng(const char *str){
	int i=0;
	while(*(str+i)) i++;
	return i;
}

void newLine(){
	if ((currentVideo-video)/((uint8_t)160) == (uint8_t)(ROW_LIMIT-1)){
		currentVideo = video;
		return;
	}

	currentVideo = ((currentVideo-video)/160+1)*160 + video;
}

uint8_t * currentline(){
	uint8_t * currentline = (currentVideo-video)/((uint8_t)160)*160 + video;
	return currentline;
}

void readInput(char * buffer){
	uint8_t * from = currentline();
	uint8_t * to = currentVideo;
	for (;from<to;){
		*buffer=*from;
		from=from+2;
		buffer++;
	}
}
