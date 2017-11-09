#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
extern opcodeGenerator();

#define NULL ((void*)0)

static int R = DR;
static int G = DG;
static int B = DB;
static int isRunning = 1;
static int timeZone = -3;

void startShell(){

	sysPrintString("Shell initialized\n", CB, CG, CR);
	char string[MAX_WORD_LENGTH] = {0};
	char lastString[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char* ch=0;

	sysPrintString("$> ",CB,CG,CR);

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
				if(isRunning) sysPrintString("$> ",CB,CG,CR);
				reset(string,strleng(string));
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

int callFunction(char * buffer) {
	if (buffer == NULL){
		return 1;
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

			return 1;
		}
		if (strcmp(input[1], "red") == 0){
			R=255;
			B=0;
			G=0;
		}
		if (strcmp(input[1], "green") == 0){
			R=0;
			B=0;
			G=255;
		}
		if (strcmp(input[1], "blue") == 0){
			R=0;
			B=255;
			G=0;
		}
		if (strcmp(input[1], "default") == 0){
			R=DR;
			B=DB;
			G=DG;
		}

		sysPrintString("Set font color\n", B, G, R);

		return 0;
	} else if (strcmp(input[0], "clear") == 0) {
		return clear(words);
	}
	else if(strcmp(input[0],"opcode")==0){
		if(words!=1){
			sysPrintString("No extra parameters for opcode\n",CB, CG, CR);
			return 1;
		}
		opcodeGenerator();
		return 0;
	}
	else if (strcmp(input[0], "calculate") == 0) {
		int ver = calculateVerifications(words, input[2], input[3]);

		if (ver) {
			int input2 = toInt(input[2]);
			int input3 = toInt(input[3]);
			int ans = calculate(input[1], input2, input3);

			sysPrintString("Calculated: ", B, G, R);
			sysPrintInt(ans, B, G, R);
			sysPrintString("\n", B, G, R);
		}

		return 0;
	} else if (strcmp(input[0], "help") == 0) {
		if(words != 2) {
			sysPrintString("No extra parameters for help\n", CB, CG, CR);

			return 1;
		}
		if(words == 2){
			if(strcmp(input[1], "echo") == 0){
				sysPrintString(ECHO_INS, B, G, R);
			}
			else if(strcmp(input[1], "displayTime") == 0){
				sysPrintString(DISPLAY_TIME_INS, B, G, R);
			}
			else if(strcmp(input[1], "setTimeZone") == 0){
				sysPrintString(SET_TIME_ZONE_INS, B, G, R);
			}
			else if(strcmp(input[1], "setFontColor") == 0){
				sysPrintString(SET_FONT_COLOR_INS, B, G, R);
			}
			else if(strcmp(input[1], "clear") == 0){
				sysPrintString(CLEAR_INS, B, G, R);
			}
			else if(strcmp(input[1], "calculate") == 0){
				sysPrintString(CALCULATE_INS, B, G, R);
			}
			else if(strcmp(input[1], "exit") == 0){
				sysPrintString(EXIT_INS, B, G, R);
			}
			else{
				sysPrintString("Not a valid command\n",CB,CG,CR);
			}
		}
		else{
			sysPrintString(helpIns, B, G, R);
		}

		return 0;
	} else if (strcmp(input[0], "exit") == 0) {
		if (words != 1) {
			sysPrintString("No extra parameters for exit\n", CB, CG, CR);

			return 1;
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

			return 1;
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

			return 1;
		}
		timeZone = toInt(input[1]);

		return 0;
	} else {
		sysPrintString("Wrong input\n", CB, CG, CR);

		return 1;
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

int graph(char input[4][MAX_WORD_LENGTH], int words) {
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


	/*sysPrintFloat(toFloat(input[1]), B, G, R);
	sysPrintString("\n", B, G, R);
	sysPrintFloat(toFloat(input[2]), B, G, R);
	sysPrintString("\n", B, G, R);
	sysPrintFloat(toFloat(input[3]), B, G, R);
	sysPrintString("\n", B, G, R);*/
	float x_r=10;
	float x_l=-10;
	float y_d=x_l;
	float y_u=x_r;
	int offset=5;
	float factor=1.5;
	char c = 0;
	int ready_to_exit = 0;

	plotFunctionFloat(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]),x_r,x_l,y_d,y_u);
	while (!ready_to_exit) {
		sysGetChar(&c);
		if (c == '\n') {
			sysClear();
			sysPrintString("Exited plot Successfully\n", CB, CG, CR);

			ready_to_exit = 1;
		}
		if (c == '+') {
			y_d/=offset;
			y_u/=offset;
			x_r/=offset;
			x_l/=offset;
			plotFunctionFloat(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]),x_r,x_l,y_d,y_u);
		}
		if (c == '-') {
			y_d*=offset;
			y_u*=offset;
			x_r*=offset;
			x_l*=offset;
			plotFunctionFloat(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]),x_r,x_l,y_d,y_u);
		}
		if (c == 15) { //UPARROW
			y_d+=offset;
			y_u+=offset;
			plotFunctionFloat(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]),x_r,x_l,y_d,y_u);
		}
		if (c == 14) { //DOWNARROW
			y_d-=offset;
			y_u-=offset;
			plotFunctionFloat(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]),x_r,x_l,y_d,y_u);
		}
		if (c == 12) { //LEFTARROW
			x_r-=offset;
			x_l-=offset;
			plotFunctionFloat(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]),x_r,x_l,y_d,y_u);
		}
		if (c == 13) { //RIGHTARROW
			x_r+=offset;
			x_l+=offset;
			plotFunctionFloat(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]),x_r,x_l,y_d,y_u);
		}
	}

	return 0;
}
