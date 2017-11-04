#include <stdint.h>
#include "videoDriver.h"
#include "font.h"

static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static unsigned char ** video_start = (unsigned char**)0x0005C28;
static unsigned int current_x = 0;
static unsigned int current_y = 0;

unsigned char * getVideoPix(){
	return *video_start;
}

void printString(uint8_t color, const char* string){
	int len = strleng(string);
	int i;
	for(i=0;i<len;i++){
		printChar(color,string[i]);
	}
}

int boundedPixel(int x, int y) {
	return (x >= 0) && (x <= SCREEN_WIDTH) && (y >= 0) && (y <= SCREEN_HEIGHT);
}

void paintPixel(int x, int y, char R, char G, char B) {
	//if (!boundedPixel(x, y))
	//	return;

	unsigned char * pixel_address;
	pixel_address = getVideoPix() + 3*(x + y*SCREEN_WIDTH);
	*pixel_address = B;
	*(pixel_address+1) = G;
	*(pixel_address+2) = R;
}

void writeChar(char c, int R, int G, int B){
	if (c < 31)
		;//DO UNPRINTABLE CHARS

	unsigned char * bitmap = pixel_map(c);
	unsigned char bitmap_aux;
	int x_counter;
	int y_counter=0;

	for(;y_counter<16;y_counter++){
		x_counter = 0;
		for(;x_counter<8;x_counter++){

			bitmap_aux = bitmap[y_counter];
			bitmap_aux >>= x_counter;

			if(bitmap_aux%2 == 1)
				paintPixel(current_x+x_counter,current_y+y_counter,R,G,B);
		}
	}
	current_x += 8;
}

int countDigits(int num){
	int dig = 1;
	while((num/=10) != 0) dig++;
	return dig;
}

void printChar(uint8_t color, char ch){
	/**currentVideo = ch;
	*(currentVideo+1) = color;
	currentVideo=currentVideo+2;*/

	writeChar(ch,255,255,255);

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

void backSpace(){
	*currentVideo=0;
	*(currentVideo-1)=0;
	currentVideo-=2;
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
