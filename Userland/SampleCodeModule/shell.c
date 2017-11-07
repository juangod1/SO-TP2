#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"

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
static int isRunning = 1;
static int timeZone = -3;

void startShell(){
	sysPrintString("Shell initialized\n", R, G, B);

	//callFunction("help");
	char string[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char* ch;
	int* ptr;

	sysPrintString("$> ",0,155,255);

	while (1) {
		sysGetChar(ch);
		sysWriteChar(*ch, B, G, R);

		string[counter]=*ch;
		(*ch != 0) ? counter++ : counter;

		if (*ch == '\n') {
			callFunction(string);
			if(isRunning) sysPrintString("$> ",0,155,255);
			reset(string);
			counter=0;
		}

		if(*ch=='\b'){
			(counter!=0)?string[counter--]=0:counter;
			(counter!=0)?string[counter--]=0:counter;
		}
	}
}

void reset(char * string, int size){
	for (int i=0; i<size; i++){
		*(string+i)=0;
	}
}
int callFunction(char* buffer){
	if (buffer == NULL){
		return 2;
	}

	int wordLength = 0;
	int words = 0;
	char input[MAX_WORDS][MAX_WORD_LENGTH] = {0};
	char* aux = buffer;

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
	/*if(words<4){
		input[words+1][wordLength-1]='\0';
		words++;
	}*/


	if(strcmp(input[0],"echo")==0){
		for(int i = 1  ;i < words+1;i++){
			sysPrintString(input[i],R,G,B);
			sysPrintString(" ",R,G,B);
		}
		sysPrintString("\n",R,G,B);
		return 0;
	}

	else if(strcmp(input[0],"setFontColor")==0){
		if(words!=2){
			sysPrintString("Wrong parameters for setFontColor\n",R,G,B);
			return 2;
		}
		//color = input[1][0]-'0'; HAS TO FIX
		sysPrintString("Set font color\n",R,G,B);
		return 0;
	}
	else if(strcmp(input[0],"clear")==0){
		if(words!=1){
			sysPrintString("No extra parameters for clear\n",R,G,B);
			return 2;
		}
		sysClear();
		return 0;
	}
	else if(strcmp(input[0],"calculate")==0){
		int ver = calculateVerifications(words, input[2],input[3]);
		if(ver){
			int input2 = toNum(input[2]);
			int input3 = toNum(input[3]);
			int rta = calculate(input[1],input2,input3);
			sysPrintString("Calculated: ",B,G,R);
			sysPrintInt(rta,B,G,R);
			sysPrintString("\n",B,G,R);
		}
		return 0;
	}
	else if(strcmp(input[0],"help")==0){
		if(words!=1){
			sysPrintString("No extra parameters for help\n",R,G,B);
			return 2;
		}
		sysPrintString(helpIns,R,G,B);
		return 0;
	}
	else if(strcmp(input[0],"exit")==0){
		if(words!=1){
			sysPrintString("No extra parameters for exit\n",R,G,B);
			return 2;
		}
		sysPrintString("See you soon",R,G,B);
		isRunning=0;
		return 0;
	}
	else if (strcmp(input[0], "graph") == 0) {
		return graph(input, words);
	} else if(strcmp(input[0],"displayTime")==0){
		int timeBuff[6];

		sysGetTime(timeBuff);
		sysPrintInt(timeBuff[2] + timeZone,R,G,B);
		sysPrintString(":",R,G,B);
		sysPrintInt(timeBuff[1],R,G,B);
		sysPrintString(":",R,G,B);
		sysPrintInt(timeBuff[0],R,G,B);

		sysPrintString(" - ",R,G,B);
		sysPrintInt(timeBuff[3],R,G,B);
		sysPrintString("/",R,G,B);
		sysPrintInt(timeBuff[4],R,G,B);
		sysPrintString("/",R,G,B);
		sysPrintInt(timeBuff[5],R,G,B);
		sysPrintString("\n",R,G,B);

		return 0;
	}
	else if(strcmp(input[0],"setTimeZone")==0){
		if(words!=2){
			sysPrintString("Wrong parameters: setTimeZone timezone\n",R,G,B);
			return 2;
		}
		timeZone = input[0];
		return 0;
	}
	else{
		sysPrintString("Wrong input\n",R,G,B);
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
		sysPrintString("Wrong parameters for calculate\n",R,G,B);
		return 0;
	}
	return 1;
}

int graph(char input[][MAX_WORD_LENGTH], int words) {
	sysPrintInt(words, B, G, R);
	if (words != (GRAPH_PARAMETERS + 1)) {
		sysPrintString("Wrong amount of parameters for graph command\n", B, G, R);

		return 2;
	}

	for (int i = 1; i <= GRAPH_PARAMETERS; i++) {
		if (!isNum(input[i])) {
			sysPrintString("Wrong parameters passed to graph command\n", B, G, R);

			return 2;
		}
	}

	plotFunctionInt(toNum(input[1]), toNum(input[2]), toNum(input[3]));

	return 0;
}
