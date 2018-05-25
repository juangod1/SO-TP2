#include "keyboardDriver.h"

const char keyMap[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b','\t',  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',  0,	/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,/*leftshift*/'\\', 'z', 'x', 'c', 'v', 'b', 'n',/* 49 */
  'm', ',', '.', '/', 0,/*rightshift*/'*', /*55*/
    0,	/* Alt -56*/
  ' ',	/* Space bar -57*/
    0,	/* Caps lock -58*/
    /*- F1 key ... > */  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,	/* < ... F10 */
    0,	/* Num lock -68*/
    0,	/* Scroll Lock -69*/
    0,	/* Home key -70*/
    15,	/* Up Arrow -71*/
    0,	/* Page Up -72*/
  '-',  /* minus -73*/
    13,	/* Left Arrow */
    0,
    12,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    14,	/* Down Arrow */
    14,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

/* Handles the keyboard interrupt */

static char circularBuffer[BUFFERSIZE]={0};
static int readindex=0;
static int writeindex=0;
static int elements=0;

static int pid = -1;
static int shift = 0;
static int alt = 0;
static int control = 0;
static int print=1;
static int caps=0;


void keyboard_handler()
{
    unsigned char scancode;
    /* Read from the keyboard's data buffer */
    scancode = get_key();

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {

  		if(scancode==182 || scancode==170){
  			shift=0;
  		}
  		if(scancode==157){
  			control=0;
  		}
  		if(scancode==184){
  			alt=0;
  		}
    }
    else
    {
      	/* Here, a key was just pressed. Please note that if you
          *  hold a key down, you will get repeated key press
          *  interrupts. */

          /* Just to show you how this works, we simply translate
          *  the keyboard scancode into an ASCII value, and then
          *  display it to the screen. You can get creative and
          *  use some flags to see if a shift is pressed and use a
          *  different layout, or you can add another 128 entries
          *  to the above layout to correspond to 'shift' being
          *  held. If shift is held using the larger lookup table,
          *  you would add 128 to the scancode when you look for it */
      if(scancode==58){ //CAPSLOCK
        caps=!caps;
      }
  		if(scancode==54 || scancode==42){ //shift
  			shift=1;
  			print=0;
  		}
  		if(scancode==29){//control
  			control=1;
  			print=0;
  		}
  		if(scancode==56){//alt
  			alt=1;
  			print=0;
  		}
  		char c=keyMap[scancode];
  		if('a'<=c && c<='z' && ((shift==1 && caps==0)||(shift==0 && caps==1))){
  			c-=('a'-'A');
  		}
      else{
        if(shift==1){
          switch(c){
            case '1':
              c='!';
              break;
            case '2':
              c='@';
              break;
            case '3':
              c='#';
              break;
            case '4':
              c='$';
              break;
            case '5':
              c='%';
              break;
            case '6':
              c='^';
              break;
            case '7':
              c='&';
              break;
            case '8':
              c='*';
              break;
            case '9':
              c='(';
              break;
            case '0':
              c=')';
              break;
            case '-':
              c='_';
              break;
            case '+':
              c='=';
              break;
            case '{':
              c='[';
              break;
            case '}':
              c=']';
              break;
            case '\\':
              c='|';
              break;
            case '=':
              c='+';
              break;
            }
        }
      }
  		if(print==1){
        putChar(c);
        if(pid!=-1){
          wakeProcess(pid);
          pid=-1;
        }

  		}
  		print=1;
    }
}

void reset(char * string, int size){
	for (int i=0; i<size; i++){
		*(string+i)=0;
	}
}
int isEmpty(){
  return elements==0;
}
void getChar(char * ch){
  if(isEmpty()){
    *ch = EOF;
    pid=getPid();
    sleepProcess(pid);
    return;
  }
  *ch=circularBuffer[readindex];
  readindex=(readindex+1)%BUFFERSIZE;
  elements--;
}

void putChar(char c){
	circularBuffer[writeindex]=c;
	writeindex=(writeindex+1)%BUFFERSIZE;
	if(elements<BUFFERSIZE){
    elements++;
	}
	else{
    readindex=(readindex+1)%BUFFERSIZE;
	}
}
