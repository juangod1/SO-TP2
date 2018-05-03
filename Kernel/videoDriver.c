#include <stdint.h>
#include "videoDriver.h"
#include "font.h"

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

void perror(const char * string){
	printString("----------------------\n",0,0,255);
	printString(string,0,0,255);
	printString("\n----------------------\n",0,0,255);
}

void printReg(char* s){
	printString(s,0,155,255);
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
			shiftVideo();
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
void printHex(uint64_t num){
	static char buffer[64] = { '0' };
	uintToBase(num,buffer,16);
	printString(buffer,0,155,255);
}
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
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
		shiftVideo();
	}
}

void shiftVideo()
{
	char * video = getVideoPix();
	memcpy(video, video+3*SCREEN_WIDTH*16, 3*SCREEN_WIDTH*(SCREEN_HEIGHT-16));
	for(int i=0; i<3*16*SCREEN_WIDTH; i++)
	{
		switch(i%2)
		{
			case 0:
				*(video+i+3*SCREEN_WIDTH*(SCREEN_HEIGHT-16))=BG_B;
			break;
			case 1:
				*(video+i+3*SCREEN_WIDTH*(SCREEN_HEIGHT-16))=BG_G;
			break;
			case 2:
				*(video+i+3*SCREEN_WIDTH*(SCREEN_HEIGHT-16))=BG_R;
			break;
			default:
			break;
		}
	}
}
