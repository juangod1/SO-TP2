#ifndef VIDEODRIVER_H_
#define VIDEODRIVER_H_

#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAX_DIGITS 20
#define ROW_LIMIT 25

void clearScreen();
void printString(uint8_t color, const char* string);
int strleng(const char *str);
int countDigits(int num);
void printInt(uint8_t color, int num);
void printChar(uint8_t color, char ch);
void newLine();
void readInput(char * buffer);
uint8_t * currentline();

#endif
