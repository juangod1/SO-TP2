#ifndef KEYBOARDDRIVER_H_
#define KEYBOARDRIVER_H_

#include <stdint.h>

extern int key_pressed();
extern int get_key();
char getChar(char * ch);
void readAllBuffer(char *);
int isEmpty();
#endif
