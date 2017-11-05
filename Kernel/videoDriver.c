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

void printString( const char* string, int R, int G, int B){
	int len = strleng(string);
	int i;
	for(i=0;i<len;i++){
		writeChar(string[i],R,G,B);
	}
}

int boundedPixel(int x, int y) {
	return (x >= 0) && (x <= SCREEN_WIDTH) && (y >= 0) && (y <= SCREEN_HEIGHT);
}

void paintPixel(int x, int y, char R, char G, char B) {
	if (!boundedPixel(x, y))
		return;

	unsigned char * pixel_address;
	pixel_address = getVideoPix() + 3*(x + y*SCREEN_WIDTH);
	*pixel_address = B;
	*(pixel_address+1) = G;
	*(pixel_address+2) = R;
}

void writeChar(char c, int R, int G, int B){
	checkLine();
	if (c < 31)
		;//DO UNPRINTABLE CHARS
	if (c =='\n'){
		newLine();
		return;
	}
	unsigned char * bitmap = pixel_map(c);
	unsigned char bitmap_aux;
	int x_counter;
	int y_counter;

	for(y_counter = 0;y_counter<16;y_counter++){
		for(x_counter = 0;x_counter<8;x_counter++){

			bitmap_aux = bitmap[y_counter];
			bitmap_aux >>= 8-x_counter;

			if(bitmap_aux%2 == 1)
				paintPixel(current_x+x_counter,current_y+y_counter,R,G,B);
		}
	}
	current_x += 8;
}
void checkLine(){
	if(current_x>=SCREEN_WIDTH){
		current_x=0;
		current_y+=16;
		if(current_y>=SCREEN_HEIGHT){
			current_y-=16;
		}
	}
}

int countDigits(int num){
	int dig = 1;
	while((num/=10) != 0) dig++;
	return dig;
}

void printInt(int num, int R, int G, int B){
		int dig = countDigits(num);
		char numbers[MAX_DIGITS] = {};
		int count=0;

		while(count!=dig){
			numbers[dig-1-count++]=num%10+48;
			num /= 10;
		}

		numbers[dig]='\0';

		if (num<0)
			writeChar('-',R,G,B);

		printString(numbers,R,G,B);
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

/*void newLine(){                                                            OLD VERSION OF NEWLINE
	if ((currentVideo-video)/((uint8_t)160) == (uint8_t)(ROW_LIMIT-1)){
		currentVideo = video;
		return;
	}

	currentVideo = ((currentVideo-video)/160+1)*160 + video;
}*/

void newLine(){
	current_x=0;
	current_y+=16;
	if(current_y>=SCREEN_HEIGHT){
		current_y--;
		shift();
	}
}
void shift(){
	return;            // ESTA FUNCION TENDRIA QUE MOVER TODO PARA ARRIBA
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
