#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
extern opcodeGenerator();

#define NULL ((void*)0)
char* helpIns ="echo *param*...			- Prints param (max of 32) to screen\n\
				displayTime 			- Prints date and time to screen\n\
				setTimeZone       - Set timezone \n\
				setFontColor *param* 	- Changes font color to the one corresponding to d\n\
				clear 					- Clears screen\n\
				calculate(*p*,*p*,*p*)	- Performs specified calculation in first variable\n\
											possible options are add, substract, divide and multiply\n\
				help 					- Displays help instructions\n\
				exit					- Exits the shell\n";
static int R = 0;
static int G = 255;
static int B = 255;
static int CR = 255;
static int CG = 255;
static int CB = 0;
static int isRunning = 1;
static int timeZone = -3;

void startShell(){
	sysPrintString("Shell initialized\n", CB, CG, CR);

	//callFunction("help");
	char string[MAX_WORD_LENGTH] = {0};
	char lastString[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char* ch;
	int* ptr;

	sysPrintString("$> ",0,155,255);

	while (isRunning) {
		sysGetChar(ch);
		if(counter<MAX_WORD_LENGTH || *ch == '\n'|| *ch == '\b'){
			sysWriteChar(*ch, B, G, R);

			string[counter]=*ch;
			(*ch != 0) ? counter++ : counter;

			if (*ch == '\n') {
				reset(lastString,strleng(lastString));
				copy(lastString,string,strleng(string)-1);
				callFunction(string);
				if(isRunning) sysPrintString("$> ",0,155,255);
				reset(string);
				counter=0;
			}

			if(*ch=='\b'){
				(counter!=0)?string[counter--]=0:counter;
				(counter!=0)?string[counter--]=0:counter;
			}
			if(*ch==15 && counter==1){ //UPARROW
				int len=strleng(lastString);
				sysPrintString(lastString, B, G, R);
				copy(string,lastString,len);
				counter=len;
			}
			if(*ch==14){
				while(counter){
					sysWriteChar('\b',B,G,R);
					(counter!=0)?string[counter--]=0:counter;
					(counter!=0)?string[counter]=0:counter;
				}
			}
		}
	}
}


void reset(char * string, int size){
	for (int i = 0; i < size; i++){
		*(string + i)=0;
	}
}

int callFunction(char * buffer) {
	if (buffer == NULL){
		return 2;
	}

	int wordLength = 0;
	int words = 0;
	char input[MAX_WORDS][MAX_WORD_LENGTH] = {0};
	char * aux = buffer;

	while (*aux != '\0' && wordLength < MAX_WORD_LENGTH) {
		if(*aux == ' ' || *aux == '\n') {
			input[words][wordLength]='\0';
			wordLength=0;
			words++;
		} else {
			input[words][wordLength] = *aux;
			wordLength++;
		}

		aux++;
	}
	

	if (strcmp(input[0], "echo") == 0) {
		return echo(input, words);
	} else if (strcmp(input[0], "setFontColor") == 0) {
		if (words != 2) {
			sysPrintString("Wrong parameters for setFontColor\n", CB, CG, CR);

			return 2;
		}
		//color = input[1][0]-'0'; HAS TO FIX
		sysPrintString("Set font color\n", B, G, R);

		return 0;
	} else if (strcmp(input[0], "clear") == 0) {
		return clear(words);
	}
	else if(strcmp(input[0],"opcode")==0){
		if(words!=1){
			sysPrintString("No extra parameters for opcode\n",color_red,color_green,color_blue);
			return 2;
		}
		opcodeGenerator();
		return 0;
	}
	} else if (strcmp(input[0], "calculate") == 0) {
		int ver = calculateVerifications(words, input[2], input[3]);

		if (ver) {
			int input2 = toNum(input[2]);
			int input3 = toNum(input[3]);
			int ans = calculate(input[1], input2, input3);

			sysPrintString("Calculated: ", B, G, R);
			sysPrintInt(ans, B, G, R);
			sysPrintString("\n", B, G, R);
		}

		return 0;
	} else if (strcmp(input[0], "help") == 0) {
		if(words != 1) {
			sysPrintString("No extra parameters for help\n", CB, CG, CR);

			return 2;
		}

		sysPrintString(helpIns, B, G, R);

		return 0;
	} else if (strcmp(input[0], "exit") == 0) {
		if (words != 1) {
			sysPrintString("No extra parameters for exit\n", CB, CG, CR);

			return 2;
		}
		sysClear();
		sysPrintString("See you soon", CB, CG, CR);

		isRunning = 0;

		return 0;
	} else if (strcmp(input[0], "graph") == 0) {
		return graph(input, words);
	} else if (strcmp(input[0],"displayTime") == 0) {
		if(words != 1) {
			sysPrintString("Wrong parameters: displayTime\n", CB, CG, CR);

			return 2;
		}
		int timeBuff[6];

		sysGetTime(timeBuff);
		sysPrintInt((timeBuff[2] + timeZone)%24, B, G, R);
		sysPrintString(":", B, G, R);
		sysPrintInt(timeBuff[1], B, G, R);
		sysPrintString(":", B, G, R);
		sysPrintInt(timeBuff[0], B, G, R);

		sysPrintString(" - ", B, G, R);
		sysPrintInt(timeBuff[3], B, G, R);
		sysPrintString("/", B, G, R);
		sysPrintInt(timeBuff[4], B, G, R);
		sysPrintString("/", B, G, R);
		sysPrintInt(timeBuff[5], B, G, R);
		sysPrintString("\n", B, G, R);

		return 0;
	} else if(strcmp(input[0],"setTimeZone") == 0) {
		if(words != 2) {
			sysPrintString("Wrong parameters: setTimeZone timezone\n", CB, CG, CR);

			return 2;
		}
		timeZone = toNum(input[1]);

		return 0;
	} else {
		sysPrintString("Wrong input\n", CB, CG, CR);

		return 2;
	}

	return 1;
}


int calculate(char* func, int param1, int param2){

	int (*operations[4]) (int x, int y);
	operations[0] = add;
	operations[1] = subtract;
	operations[2] = multiply;
	operations[3] = divide;
	char * operationsName[4] = {"add", "subtract", "multiply", "divide"};

	for (int i = 0; i < 4; ++i)
	{
		if (strcmp(func, operationsName[i]) == 0)
		{
			return operations[i](param1, param2);
		}
	}

	return 0;
}

int calculateVerifications(int words, char* input2, char* input3){
	if(words!=4 || !isNum(input2) || !isNum(input3) ){
		//veryfing that there are four inputs and that the last two are numbers
		sysPrintString("Wrong parameters for calculate\n", CB, CG, CR);
		return 0;
	}
	return 1;
}

int overflowGenerator(int n){
	char szBuf[1024] = { '\0' };
	int x = (n*(n+77)*(n+23)*(n+17)+n)%1024;
	szBuf[x]=n;
	return (n>0)? overflowGenerator(n-1) : x;
}
int echo(char input[][MAX_WORD_LENGTH], int words) {
	for (int i = 1  ;i < (words + 1); i++) {
		sysPrintString(input[i], B, G, R);
		sysPrintString(" ", B, G, R);
	}

	sysPrintString("\n", B, G, R);

	return 0;
}

int clear(int words) {
	if (words != 1) {
		sysPrintString("No extra parameters for clear\n", CB, CG, CR);

		return 2;
	}

	sysClear();

	return 0;
}

int graph(char input[][MAX_WORD_LENGTH], int words) {
	if (words != (GRAPH_PARAMETERS + 1)) {
		sysPrintString("Wrong amount of parameters for graph command\n\
		Use command help for guidelines\n", CB, CG, CR);

		return 2;
	}

	for (int i = 1; i <= GRAPH_PARAMETERS; i++) {
		if (!isNum(input[i])) {
			sysPrintString("Wrong parameters passed to graph command\n\
			Use command help for guidelines\n", CB, CG, CR);

			return 2;
		}
	}

	plotFunctionInt(toNum(input[1]), toNum(input[2]), toNum(input[3]));
	char* c=0;
	int exitFlag=0;
	while(exitFlag==0){
		sysGetChar(c);
		if(*c=='\n'){
			sysClear();
			sysPrintString("Exited plot Successfully\n", CB, CG, CR);
			return 0;
		}
	}
}
