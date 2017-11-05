#include "stdLib.h";
#include "stdio.h";
#define NULL ((void*)0)
char* helpIns ="\necho *param*...			- prints param (max of 32) to screen\n\
				displayTime 			- prints date and time to screen\n\
				setFontColor *param* 	- changes font color to the one corresponding to d\n\
				clear 					- clears screen\n\
				calculate(*p*,*p*,*p*)	- performs specified calculation in first variable\n\
											possible options are add, substract, divide and multiply\n\
				help 					- displays help instructions\n\
				exit					- exits the shell\n";
static int color_red=0;
static int color_green=0;
static int color_blue=0;

void startShell(){
	sysPrintString("Shell initialized",color_red,color_green,color_blue);
	callFunction("help\n");
	char string[80]={0};
	int counter=0;
	char* ch;
	int* ptr;
	sysPrintString(";) Mamita que pedazo de animacion ;)\n",color_red,color_green,color_blue);
	sysPrintString("$> ",0,0,0);
	while(1){
		sysGetChar(ch);
		sysWriteChar(*ch);
		string[counter]=*ch;
		(*ch!=0)?counter++:counter;
		if(*ch=='\n'){
			callFunction(string);
			sysPrintString("$> ",0,0,0);
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
		if(*aux==' '){
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
		return 0;
	}

	else if(strcmp(input[0],"displayTime\n")==0){
		if(words!=1){
			sysPrintString("Wrong parameters for displayTime",color_red,color_green,color_blue);
			return 2;
		}
		sysPrintString("Displaying time",color_red,color_green,color_blue);
		//sysGetTime(buffer);
		return 0;
	}
	else if(strcmp(input[0],"setFontColor\n")==0){
		if(words!=2){
			sysPrintString("Wrong parameters for setFontColor",color_red,color_green,color_blue);
			return 2;
		}
		//color = input[1][0]-'0'; HAS TO FIX
		sysPrintString("Set font color",color_red,color_green,color_blue);
		return 0;
	}
	else if(strcmp(input[0],"clear\n")==0){
		if(words!=1){
			sysPrintString("No extra parameters for clear",color_red,color_green,color_blue);
			return 2;
		}
		sysClear();
		return 0;
	}
	else if(strcmp(input[0],"calculate\n")==0){
		//verificar que hay 4 inputs
		if(words!=4){
			sysPrintString("Wrong parameters for calculate",color_red,color_green,color_blue);
			return 2;
		}
		int rta = calculate(input[1],input[2][0]-'0',input[3][0]-'0');
		sysPrintString("Calculating: ",color_red,color_green,color_blue);
		sysPrintInt(rta,color_red,color_green,color_blue);
		return 0;
	}
	else if(strcmp(input[0],"help\n")==0){
		if(words!=1){
			sysPrintString("No extra parameters for help",color_red,color_green,color_blue);
			return 2;
		}
		sysPrintString(helpIns,color_red,color_green,color_blue);
		return 0;
	}
	else if(strcmp(input[0],"exit\n")==0){
		if(words!=1){
			sysPrintString("No extra parameters for exit",color_red,color_green,color_blue);
			return 2;
		}
		sysPrintString("See you soon",color_red,color_green,color_blue);
		return 0;
	}
	else if(strcmp(input[0],"graph\n")==0){
		if(words!=1){
			sysPrintString("No extra parameters for graph",color_red,color_green,color_blue);
			return 2;
		}
		//graph();
		return 0;
	}
	else{
		sysPrintString("Wrong input\n",color_red,color_green,color_blue);
		sysPrintString(input[0],color_red,color_green,color_blue);
		return 2;
	}
	return 1;
}

int add(int x, int y) {
	return x + y;
}

int subtract(int x, int y) {
	return x - y;
}

int multiply(int x, int y) {
	return x * y;
}

int divide(int x, int y) {
	return x / y;
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
