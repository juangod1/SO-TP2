#ifndef VIDEODRIVER_H_
#define VIDEODRIVER_H_

#include <stdint.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define MAX_DIGITS 20
#define ROW_LIMIT 25
#define BG_R 0
#define BG_G 0
#define BG_B 0
#define color_red 0
#define color_green 0
#define color_blue 0
#define PIXELS_PER_LINE 16
#define PIXELS_PER_CHARSPACE 8
#define HMAX 1600

void clearScreen();
void printString(const char* string, int R, int G, int B);
int strleng(const char *str);
void printInt(int num, int R, int G, int B);
void printHex(uint64_t num, int B, int G, int R);
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);
void newLine();
void readInput(char * buffer);
int isPixelColor(int x, int y, int B, int G, int R);
uint8_t * currentline();
int boundedPixel(int x, int y);
void paintPixel(int x, int y, char R, char G, char B);
unsigned char * getVideoPix();
void writeChar(char c, int R, int G, int B);
void paintCharSpace(int current_x, int current_y, char B, char G, char R);
void checkLine();
void backSpace();
void shiftVideo(int lines, int upwards);
void paintBackGround();
void perror(const char * string);
void resetScreenCoordinates();
void finalizeScreenBuffer();
void initializeScreenBuffer();


#endif
