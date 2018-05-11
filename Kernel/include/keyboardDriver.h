#ifndef KEYBOARDDRIVER_H_
#define KEYBOARDRIVER_H_


#include "videoDriver.h"

#define BUFFERSIZE 20
#define EOF 0

extern int key_pressed();
extern int get_key();
void getChar(char * ch);
void readAllBuffer(char *);
int isEmpty();
void putChar(char c);
void keyboard_handler();

#endif
