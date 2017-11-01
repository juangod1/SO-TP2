#include "stdLib.h";
#include "stdio.h";

char* helpIns ="echo *param*			- prints s to screen\n\
				displayTime 			- prints date and time to screen\n\
				setFontColor *param* 	- changes font color to the one corresponding to d\n\
				clear 					- clears screen\n\
				calculate(*p*,*p*,*p*)	- performs specified calculation in first variable\n\
				help 					- displays help instructions\n\
				exit					- exits the shell\n";
int color=2;

void startShell(){
	sysPrintString(2,"Shell initialized");
	while(1){
		//int c = getChar();
		//putChar();
	}
}
int callFunction(char*buffer){
	
	
	if(strcmp(buffer,"echo")==0){
		sysPrintString(2,"Echo");
		sysNewLine();
		return 0;
	}
	else if(strcmp(buffer,"displayTime")==0){
		sysPrintString(2,"Displaying time");
		sysGetTime(buffer);
		sysNewLine();
		return 0;
	}
	else if(strcmp(buffer,"setFontColor")==0){
		sysPrintString(2,"Setting font color");
		sysNewLine();
		return 0;
	}
	else if(strcmp(buffer,"clear")==0){
		sysPrintString(2,"Clearing screen");
		sysNewLine();
		return 0;
	}
	else if(strcmp(buffer,"calculate")){
		sysPrintString(2,"Calculating");
		sysNewLine();
	}
	else if(strcmp(buffer,"help")==0){
		sysPrintString(2,helpIns);
		sysNewLine();
		return 0;
	}
	else if(strcmp(buffer,"exit")==0){
		sysPrintString(2,"See you soon");
		sysNewLine();
		return 0;
	}
	else{
		sysPrintString(4,"Wrong input");
		sysNewLine();
		return 0;
	}
	return 1;
}