#include "keyboardDriver.h"

const char keyMap[] ={0,0, '1', '2', '3', '4', '5',\
 '6', '7', '8', '9', '0', '\'', '¿', '\b','\t',\
'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', \
0, '+', '\n',0, 'a', 's', 'd', 'f', 'g', 'h',\
 'j', 'k', 'l', 'n', '{', '|', 0,'}', 'z', 'x', \
 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0, 0,\
 0, ' ' };

char getChar(){
  int pressed = 0;
  while(!pressed)
    pressed = key_pressed();

  return keyMap[get_key()];
}
