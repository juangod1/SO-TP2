#include <stdint.h>
#include "videoDriver.h"
#include "include/lib.h"
#include "font.h"
#include "testLib.h"
#include "lib.h"

static unsigned char ** video_start = (unsigned char**)0x0005C28;
static unsigned int current_x = 0;
static unsigned int current_y = 0;

int h= HMAX/2;
char * screenBuffer=NULL;

void initializeScreenBuffer()
{
	finalizeScreenBuffer();
	screenBuffer=malloc(HMAX*SCREEN_WIDTH*3);
}
void finalizeScreenBuffer()
{
	free(screenBuffer);
	screenBuffer=NULL;
}

void swapScreenColors(int oB, int oG, int oR, int nB, int nG, int nR)
{
	for(int i=0; i<SCREEN_WIDTH; i+=1){
		for(int j=0; j<SCREEN_HEIGHT; j+=1){
			if(isPixelColor(i,j,oB,oG,oR))
			{
				paintPixel(i,j,nB,nG,nR);
			}
		}
	}
	resetScreenCoordinates();
}

int isPixelColor(int x, int y, int B, int G, int R)
{
	//Could check if boundedPixel() but might be a lot of work for little purpose since this is read only.
	unsigned char * pixel_address;
	pixel_address = getVideoPix() + 3*(x + y*SCREEN_WIDTH);
	if(*pixel_address==B && *(pixel_address+1)==G && *(pixel_address+2)==R)
	{
		return 1;
	}
	return 0;
}

void resetScreenCoordinates()
{
	current_x=0;
	current_y=SCREEN_HEIGHT-PIXELS_PER_LINE;
}

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

void perror(const char * string)
{
	printString(string,TB_FAIL,TG_FAIL,TR_FAIL);
	printString("\n",TB_FAIL,TG_FAIL,TR_FAIL);
}

int boundedPixel(int x, int y) {
	return (x >= 0) && (x <= SCREEN_WIDTH) && (y >= 0) && (y <= SCREEN_HEIGHT);
}

void paintBackGround(){
	for(int i=0; i<SCREEN_WIDTH; i+=PIXELS_PER_CHARSPACE){
		for(int j=0; j<SCREEN_HEIGHT; j+=PIXELS_PER_LINE){
			paintCharSpace(i,j,BG_B,BG_G,BG_R);
		}
	}
}

void paintCharSpace(int current_x, int current_y, char B, char G, char R){
	for(int i=0; i<PIXELS_PER_CHARSPACE; i++){
		for(int j=0; j<PIXELS_PER_LINE; j++){
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

		for(y_counter = 0;y_counter<PIXELS_PER_LINE;y_counter++){
			for(x_counter = 0;x_counter<PIXELS_PER_CHARSPACE;x_counter++){

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
	if(current_x > 3*PIXELS_PER_CHARSPACE){
		current_x-=PIXELS_PER_CHARSPACE;
		paintCharSpace(current_x, current_y, BG_B, BG_G, BG_R);
	}
}
void checkLine(){
	if(current_x>=SCREEN_WIDTH){
		current_x=0;
		current_y+=PIXELS_PER_LINE;
		if(current_y>=SCREEN_HEIGHT){
			current_y-=PIXELS_PER_LINE;
			shiftVideo(PIXELS_PER_LINE, 0);
		}
	}
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
void printHex(uint64_t num, int B, int G, int R){
	static char buffer[64] = { '0' };
	uintToBase(num,buffer,16);
	printString(buffer,B,G,R);
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
	for(int i=0; i<SCREEN_WIDTH; i+=PIXELS_PER_CHARSPACE){
		for(int j=0; j<SCREEN_HEIGHT; j+=PIXELS_PER_LINE){
			paintCharSpace(i,j,BG_B,BG_G,BG_R);
		}
	}
	resetScreenCoordinates();
}

int strleng(const char *str){
	int i=0;
	while(*(str+i)) i++;
	return i;
}

void newLine(){
	current_x=0;
	current_y+=PIXELS_PER_LINE;
	if(current_y>=SCREEN_HEIGHT){
		current_y-=PIXELS_PER_LINE;
		createNewLines(PIXELS_PER_LINE);
	}
}

void createNewLines(int lines)
{
	char * video = (char *) getVideoPix();
	char * aux =malloc(3*SCREEN_WIDTH*lines);
	memcpy(aux,video, 3*SCREEN_WIDTH*lines);
	memcpy(video, video+3*SCREEN_WIDTH*lines, 3*SCREEN_WIDTH*(SCREEN_HEIGHT-lines));
	memcpy(screenBuffer,screenBuffer+3*SCREEN_WIDTH*lines,3*SCREEN_WIDTH*(HMAX-lines));
	memcpy(screenBuffer+3*SCREEN_WIDTH*(HMAX-lines),aux,3*SCREEN_WIDTH*lines);
	free(aux);
	for(int i=0; i<3*lines*SCREEN_WIDTH; i++)
	{
		switch(i%2)
		{
			case 0:
				*(video+i+3*SCREEN_WIDTH*(SCREEN_HEIGHT-lines))=BG_B;
			break;
			case 1:
				*(video+i+3*SCREEN_WIDTH*(SCREEN_HEIGHT-lines))=BG_G;
			break;
			case 2:
				*(video+i+3*SCREEN_WIDTH*(SCREEN_HEIGHT-lines))=BG_R;
			break;
			default:
			break;
		}
	}
}

void shiftVideo(int lines, int upwards)
{
	if(upwards)
	{
		shiftUpwards();
	}
	else
	{
		shiftDownards();
	}
}
void shiftUpwards(int lines)
{
	for(int i=0; i<lines; i++)
	{
		shiftOneLineUpwards();
	}
}
void shiftOneLineUpwards()
{
	if(h<=0)
	{
		printString("hmin",0,0,255);
		return;
 	}
	char * screen = getVideoPix();
	char * aux =malloc(3*SCREEN_WIDTH);

	memcpy(aux,screen+3*SCREEN_WIDTH*(SCREEN_HEIGHT-1), 3*SCREEN_WIDTH);
	memcpy(screen+3*SCREEN_WIDTH,screen, 3*SCREEN_WIDTH*(SCREEN_HEIGHT-1));
	h--;
	memcpy(screen, screenBuffer+3*SCREEN_WIDTH*h, 3*SCREEN_WIDTH);
	memcpy(screenBuffer+3*SCREEN_WIDTH*h, aux, 3*SCREEN_WIDTH);

	free(aux);

}
void shiftDownards(int lines)
{
	for(int i=0; i<lines; i++)
	{
		shiftOneLineDownwards();
	}
}
void shiftOneLineDownwards()
{
	if(h<=0)
	{
		printString("hmax",0,0,255);
		return;
 	}
	char * screen=getVideoPix();
	char * aux=malloc(3*SCREEN_WIDTH);

	memcpy(aux,screen,3*SCREEN_WIDTH);
	memcpy(screen, screen+3*SCREEN_WIDTH*h, 3*SCREEN_WIDTH*(SCREEN_HEIGHT-1));
	memcpy(screen+3*SCREEN_WIDTH*(SCREEN_HEIGHT-1),screenBuffer+3*SCREEN_WIDTH*h,3*SCREEN_WIDTH);
	memcpy(screenBuffer+3*SCREEN_WIDTH*h,aux,3*SCREEN_WIDTH);

	free(aux);
}
