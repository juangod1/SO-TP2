#include "keyboardDriver.h"
#include "videoDriver.h"
#define BUFFERSIZE 20
#define EOF 0

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
    0,	/* Up Arrow -71*/
    0,	/* Page Up -72*/
  '-',  /* minus -73*/
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

/** ACORDARSE DE AVISAR QUE ROBAMOS TODO ESTE CODIGO DE http://www.osdever.net/bkerndev/Docs/keyboard.htm **/
/* Handles the keyboard interrupt */



static char circularBuffer[BUFFERSIZE]={0};
static int readindex=0;
static int writeindex=0;
static int elements=0;

static int shift = 0;
static int alt = 0;
static int control = 0;
static int print=1;


void keyboard_handler(struct regs *r)
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
		if('a'<=c && c<='z' && shift==1){
			c-=('a'-'A');
		}
		if(print==1){
        	putChar(c);
		}
		if(control && alt && shift){ //print BUFFER
			char buff[BUFFERSIZE];	//	SE VA A TENER
			readAllBuffer(buff);	//	QUE BORRAR EN
			printString(buff,255,255,255);	//	UN FUTURO
			reset(buff,BUFFERSIZE);	//	ES PARA TESTING
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
char getChar(char * ch){
  if(isEmpty()){
    *ch= EOF;
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

void readAllBuffer(char* buff){
	if(elements==0){
		*buff=EOF;
	}
	else{
		int counter=0;
		while(elements>0){
			*(buff+counter)=circularBuffer[readindex];
			counter++;
			readindex=(readindex+1)%20;
			elements--;
		}
    *(buff+counter)=0;
	}

}

char getBuffer(){}
