#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"

#define NULL ((void*)0)
char* helpIns ="echo *param*...			- prints param (max of 32) to screen\n\
				displayTime 			- prints date and time to screen\n\
				setFontColor *param* 	- changes font color to the one corresponding to d\n\
				clear 					- clears screen\n\
				calculate(*p*,*p*,*p*)	- performs specified calculation in first variable\n\
											possible options are add, substract, divide and multiply\n\
				help 					- displays help instructions\n\
				exit					- exits the shell\n";
static int color_red=0;
static int color_green=255;
static int color_blue=255;
static int isRunning=1;
static int timeZone=-3;

void startShell(){

	sysPrintString("Shell initialized\n",color_red,color_green,color_blue);

	callFunction("help");
	char string[80]={0};
	int counter=0;
	char* ch;
	int* ptr;
	sysPrintString("$> ",0,155,255);
	while(1){

		sysGetChar(ch);
		sysWriteChar(*ch,color_blue,color_green,color_red);
		string[counter]=*ch;
		(*ch!=0)?counter++:counter;
		if(*ch=='\n'){
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
	if(buffer==NULL){
		return 2;
	}
	int wordLength=0;
	int words = 0;
	char input[32][80]={0};
	char* aux = buffer;
	while(*aux!='\0' && wordLength<80){
		if(*aux==' ' || *aux=='\n'){
			input[words][wordLength]='\0';
			wordLength=0;
			words++;
		}
		else{
			input[words][wordLength] = *aux;
			wordLength++;
		}

		aux++;
	}
	if(words<4){
		input[words+1][wordLength-1]='\0';
		words++;
	}


	if(strcmp(input[0],"echo")==0){
		for(int i = 1  ;i < words+1;i++){
			sysPrintString(input[i],color_red,color_green,color_blue);
			sysPrintString(" ",color_red,color_green,color_blue);
		}
		sysPrintString("\n",color_red,color_green,color_blue);
		return 0;
	}

	else if(strcmp(input[0],"setFontColor")==0){
		if(words!=2){
			sysPrintString("Wrong parameters for setFontColor\n",color_red,color_green,color_blue);
			return 2;
		}
		//color = input[1][0]-'0'; HAS TO FIX
		sysPrintString("Set font color\n",color_red,color_green,color_blue);
		return 0;
	}
	else if(strcmp(input[0],"clear")==0){
		if(words!=1){
			sysPrintString("No extra parameters for clear\n",color_red,color_green,color_blue);
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
			sysPrintInt(input2,0,0,0);
			sysPrintString("\n",color_blue,color_green,color_red);
			sysPrintInt(input3,0,0,0);
			sysPrintString("\n",color_blue,color_green,color_red);
			int rta = calculate(input[1],input2,input3);
			sysPrintString("Calculated: ",color_blue,color_green,color_red);
			sysPrintInt(rta,color_blue,color_green,color_red);
			sysPrintString("\n",color_blue,color_green,color_red);
		}
		return 0;
	}
	else if(strcmp(input[0],"help")==0){
		if(words!=1){
			sysPrintString("No extra parameters for help\n",color_red,color_green,color_blue);
			return 2;
		}
		sysPrintString(helpIns,color_red,color_green,color_blue);
		return 0;
	}
	else if(strcmp(input[0],"exit")==0){
		if(words!=1){
			sysPrintString("No extra parameters for exit\n",color_red,color_green,color_blue);
			return 2;
		}
		sysPrintString("See you soon",color_red,color_green,color_blue);
		isRunning=0;
		return 0;
	}
	else if(strcmp(input[0],"graph\n")==0){
		if(words!=1){
			sysPrintString("No extra parameters for graph",color_red,color_green,color_blue);
			return 2;
		}
		plotFunctionInt(0, 1, 0);
		return 0;
	}
	else if(strcmp(input[0],"displayTime")==0){
		int timeBuff[6];

		sysGetTime(timeBuff);
		sysPrintInt(timeBuff[2] + timeZone,color_red,color_green,color_blue);
		sysPrintString(":",color_red,color_green,color_blue);
		sysPrintInt(timeBuff[1],color_red,color_green,color_blue);
		sysPrintString(":",color_red,color_green,color_blue);
		sysPrintInt(timeBuff[0],color_red,color_green,color_blue);

		sysPrintString(" - ",color_red,color_green,color_blue);
		sysPrintInt(timeBuff[3],color_red,color_green,color_blue);
		sysPrintString("/",color_red,color_green,color_blue);
		sysPrintInt(timeBuff[4],color_red,color_green,color_blue);
		sysPrintString("/",color_red,color_green,color_blue);
		sysPrintInt(timeBuff[5],color_red,color_green,color_blue);
		sysPrintString("\n",color_red,color_green,color_blue);

		return 0;
	}
	else{
		sysPrintString("Wrong input\n",color_red,color_green,color_blue);
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
		sysPrintString("Wrong parameters for calculate\n",color_red,color_green,color_blue);
		return 0;
	}
	return 1;
}
