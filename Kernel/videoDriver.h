#ifndef VIDEODRIVER_H_
#define VIDEODRIVER_H_

#include <stdint.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define MAX_DIGITS 20

void clearScreen();
void printString(uint8_t color, const char* string);
int strleng(const char *str);
int countDigits(int num);
void printInt(uint8_t color, int num);
void printChar(uint8_t color, char ch);
void newLine();

#endif
