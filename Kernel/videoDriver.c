#include <stdint.h>
#include "videoDriver.h"
#include "font.h"


static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static unsigned char ** video_start = (unsigned char**)0x0005C28;
static unsigned int current_x = 0;
static unsigned int current_y = SCREEN_HEIGHT-16;

unsigned char * getVideoPix(){
	return *video_start;
}

void printString( const char* string, int B, int G, int R){
	int len = strleng(string);
	int i;
	for(i=0;i<len;i++){
		writeChar(string[i],B,G,R);
	}
}

int boundedPixel(int x, int y) {
	return (x >= 0) && (x <= SCREEN_WIDTH) && (y >= 0) && (y <= SCREEN_HEIGHT);
}

void paintBackGround(){
	for(int i=0; i<SCREEN_WIDTH; i+=8){
		for(int j=0; j<SCREEN_HEIGHT; j+=16){
			paintCharSpace(i,j,BG_B,BG_G,BG_R);
		}
	}
}

void paintCharSpace(int current_x, int current_y, char B, char G, char R){
	for(int i=0; i<8; i++){
		for(int j=0; j<16; j++){
			paintPixel(current_x+i, current_y+j, B, G, R);
		}
	}
}

void paintPixel(int x, int y, char B, char G, char R) {
	if (!boundedPixel(x, y))
		return;

	unsigned char * pixel_address;
	pixel_address = getVideoPix() + 3*(x + y*SCREEN_WIDTH);
	*pixel_address = B;
	*(pixel_address+1) = G;
	*(pixel_address+2) = R;
}

void writeChar(char c, int B, int G, int R){
	checkLine();
	if (c < 31){
		if (c =='\n'){
			newLine();
			return;
		}
		if (c== 8){	//BACKSPACE
			backSpace();
			return;
		}
	}
	else{
		unsigned char * bitmap = pixel_map(c);
		unsigned char bitmap_aux;
		int x_counter;
		int y_counter;

		for(y_counter = 0;y_counter<16;y_counter++){
			for(x_counter = 0;x_counter<8;x_counter++){

				bitmap_aux = bitmap[y_counter];
				bitmap_aux >>= 8-x_counter;

				if(bitmap_aux%2 == 1)
					paintPixel(current_x+x_counter,current_y+y_counter,B,G,R);
				else{
					paintPixel(current_x+x_counter,current_y+y_counter,BG_B,BG_G,BG_R);
				}
			}
		}
		current_x += 8;
	}
}
void backSpace(){
	if(current_x > 3*8){
		current_x-=8;
		paintCharSpace(current_x, current_y, BG_B, BG_G, BG_R);
	}
}
void checkLine(){
	if(current_x>=SCREEN_WIDTH){
		current_x=0;
		current_y+=16;
		if(current_y>=SCREEN_HEIGHT){
			current_y-=16;
			shift();
		}
	}
}

int countDigits(int num){
	int dig = 1;
	while((num/=10) != 0) dig++;
	return dig;
}

void printInt(int num, int B, int G, int R){
		int dig = countDigits(num);
		char numbers[MAX_DIGITS] = {};
		int count=0;

		while(count!=dig){
			numbers[dig-1-count++]=num%10+48;
			num /= 10;
		}

		numbers[dig]='\0';

		if (num<0)
			writeChar('-',B,G,R);

		printString(numbers,B,G,R);
}

void clearScreen(){
	for(int i=0; i<SCREEN_WIDTH; i+=8){
		for(int j=0; j<SCREEN_HEIGHT; j+=16){
			paintCharSpace(i,j,BG_B,BG_G,BG_R);
		}
	}
	current_x=0;
	current_y=SCREEN_HEIGHT-16;
}

int strleng(const char *str){
	int i=0;
	while(*(str+i)) i++;
	return i;
}

void newLine(){
	current_x=0;
	current_y+=16;
	if(current_y>=SCREEN_HEIGHT){
		current_y-=16;
		shift();
	}
}
void shift(){
	unsigned char B;
	unsigned char G;
	unsigned char R;
	unsigned char * pixel_address;
	for(int i=0; i<SCREEN_WIDTH;i++){
		for(int j=16; j<SCREEN_HEIGHT;j++){
			pixel_address = getVideoPix() + 3*(i + j*SCREEN_WIDTH);
			B=*(pixel_address);
			G=*(pixel_address+1);
			R=*(pixel_address+2);
			paintPixel(i,j-16,B,G,R);
		}
	}
	int j=SCREEN_HEIGHT-16;
	for(int i=0; i<SCREEN_WIDTH;i+=8){
		paintCharSpace(i,j,BG_B,BG_G,BG_R);
	}
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
