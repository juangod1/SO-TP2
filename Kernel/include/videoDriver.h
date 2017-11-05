#ifndef VIDEODRIVER_H_
#define VIDEODRIVER_H_

#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAX_DIGITS 20
#define ROW_LIMIT 25
#define BG_R 0
#define BG_G 255
#define BG_B 255
#define color_red 0
#define color_green 0
#define color_blue 0

void clearScreen();
void printString(const char* string, int R, int G, int B);
int strleng(const char *str);
int countDigits(int num);
void printInt(int num, int R, int G, int B);
void newLine();
void readInput(char * buffer);
uint8_t * currentline();
int boundedPixel(int x, int y);
void paintPixel(int x, int y, char R, char G, char B);
unsigned char * getVideoPix();
void writeChar(char c, int R, int G, int B);
void plotAxis();
void plotFunction(float a, float b, float c);

#endif
