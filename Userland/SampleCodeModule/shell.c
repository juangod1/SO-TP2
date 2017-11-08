#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
extern opcodeGenerator();

#define NULL ((void*)0)
const char* helpIns =
				"echo arguments ...          - Prints arguments\n\
				displayTime                 - Prints date and time to screen\n\
				setTimeZone timezone        - Set timezone \n\
				setFontColor color          - Changes font color\n\
				clear                       - Clears screen\n\
				calculate operation op1 op2 - Performs specified calculation \n\
				help (optional)command      - Displays help instructions for command\n\
				exit                        - Exits the shell\n";
const char* echoIns ="Recieves a variable amount of arguments, prints them in the screen (max 32).\n";
const char* displayTimeIns ="Recieves no arguments. Prints current date and time.\n\
							Default timezone is UTC-3.\n";
const char* setTimeZoneIns ="Recieves an integer between -11 and 12.\n\
							The parameter is set as the computer timezone in\n\
							future time printings.\n";
const char* setFontColorIns ="Recieves a string (red, blue, green or default). \n\
							The fontcolor for future user printings is changed.\n";
const char* clearIns ="Removes information from screen, starts over.\n";
const char* calculateIns ="Recieves 3 arguments.\n\
							Arg 1: Operation (add, substract, multiply, divide).\n\
							Arg 2 and 3: Operands, real numbers.\n";
const char* exitIns ="Quits the shell.\n";
static int R = DR;
static int G = DG;
static int B = DB;
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
			sysPrintString("No extra parameters for opcode\n",B,G,R);
			return 2;
		}
		opcodeGenerator();
		return 0;
	}
	else if (strcmp(input[0], "calculate") == 0) {
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
		if(words > 2) {
			sysPrintString("Too many parameters for help\n", CB, CG, CR);
			return 2;
		}
		if(words == 2){
			if(strcmp(input[1], "echo") == 0){
				sysPrintString(echoIns, B, G, R);
			} 
			else if(strcmp(input[1], "displayTime") == 0){
				sysPrintString(displayTimeIns, B, G, R);				
			}
			else if(strcmp(input[1], "setTimeZone") == 0){
				sysPrintString(setTimeZoneIns, B, G, R);				
			}
			else if(strcmp(input[1], "setFontColor") == 0){
				sysPrintString(setFontColorIns, B, G, R);				
			}
			else if(strcmp(input[1], "clear") == 0){
				sysPrintString(clearIns, B, G, R);	
			}
			else if(strcmp(input[1], "calculate") == 0){
				sysPrintString(calculateIns, B, G, R);				
			}
			else if(strcmp(input[1], "exit") == 0){
				sysPrintString(exitIns, B, G, R);
			}
			else if(strcmp(input[1], "exit") == 0){
				sysPrintString(exitIns, B, G, R);
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
