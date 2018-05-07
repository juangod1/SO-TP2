#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#include "contextSwitchDemo.h"
#include "prodConsProblem.h"

static int R = DR;
static int G = DG;
static int B = DB;
static int isRunning = 1;
static int timeZone = -3;
pid_t foregroundPID = 0;

char * processNames[MAX_PROCESSES];
int processes[MAX_PROCESSES][2];
int processesAmount[1];

int foreground(pid_t pid){
    foregroundPID = pid;
}

void startShell(){
	sysPrintString("Shell initialized\n", CB, CG, CR);
	char string[MAX_WORD_LENGTH] = {0};
	char lastString[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char ch;

	sysPrintString("$> ",CB,CG,CR);

	while (isRunning) {
	    checkPipePrint(); // check if background processes wanted to print to shell
		sysGetProcesses((pid_t **)processes,processNames,processesAmount);
		sysGetChar(&ch);
		if(counter<MAX_WORD_LENGTH || ch == '\n'|| ch == '\b'){

			sysWriteChar(ch, B, G, R);


			string[counter]=ch;
			(ch != 0) ? counter++ : counter;

			if (ch == '\n') {
				reset(lastString,strleng(lastString));
				copy(lastString,string,strleng(string)-1);
				callFunction(string,0);
				if(isRunning) sysPrintString("$> ",CB,CG,CR);
				reset(string,strleng(string));
				counter=0;
			}

			if(ch=='\b'){
				(counter!=0)?string[counter--]=0:counter;
				(counter!=0)?string[counter--]=0:counter;
			}
			if(ch==15 && counter==1){ //UPARROW
				int len=strleng(lastString);
				sysPrintString(lastString, B, G, R);
				copy(string,lastString,len);
				counter=len;
			}
			if(ch==14){
				while(counter){
					sysWriteChar('\b',B,G,R);
					(counter!=0)?string[counter--]=0:counter;
					(counter!=0)?string[counter]=0:counter;
				}
			}
		}
	}
}

int callFunction(char * buffer, int backgroundflag) {
	if (buffer == NULL){
		return 1;
	}

	int wordLength = 0;
	int words = 0;
	char input[MAX_WORDS][MAX_WORD_LENGTH] = {{0}};
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
      //sysChangeScreenColors(B,G,R,255,0,0);
			R=255;
			B=0;
			G=0;
		}
		else if (strcmp(input[1], "green") == 0){
      //sysChangeScreenColors(B,G,R,0,255,0);
			R=0;
			B=0;
			G=255;
		}
		else if (strcmp(input[1], "blue") == 0){
      //sysChangeScreenColors(B,G,R,0,0,255);
			R=0;
			B=255;
			G=0;
		}
		else if (strcmp(input[1], "default") == 0){
      //sysChangeScreenColors(B,G,R,DB,DG,DR);
			R=DR;
			B=DB;
			G=DG;
		}
		else{
			sysPrintString("Wrong parameters for setFontColor\n", CB, CG, CR);
			return 1;
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
		int ver = calculateVerifications(words, input[1], input[2], input[3]);


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
		if(words > 2) {
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
			else if(strcmp(input[1], "plot") == 0){
				sysPrintString(PLOT_INS, B, G, R);
			}
			else if(strcmp(input[1], "opcode") == 0){
				sysPrintString(OPCODE_INS, B, G, R);
			}
      else if(strcmp(input[1], "test") == 0){
        sysPrintString(TEST_INS, B, G, R);
      }
      else if(strcmp(input[1], "foreground") == 0){
        sysPrintString(FOREGROUND_INS, B, G, R);
      }
      else if(strcmp(input[1], "prodConsDemo") == 0){
        sysPrintString(PRODCONS_INS, B, G, R);
      }
            else if(strcmp(input[1], "background") == 0){
                sysPrintString(BACKGROUND_INS, B, G, R);
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
	} else if (strcmp(input[0], "plot") == 0) {
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
		if(timeBuff[1]/10==0)
			sysPrintString("0",B,G,R);
		sysPrintInt(timeBuff[1], B, G, R);
		sysPrintString(":", B, G, R);
		if(timeBuff[0]/10==0)
			sysPrintString("0",B,G,R);
		sysPrintInt(timeBuff[0], B, G, R);

		sysPrintString(" - ", B, G, R);
		if((timeBuff[2] + timeZone)/24!=0)
			sysPrintInt(timeBuff[3]+1, B, G, R);
		else
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
		if(toInt(input[1])>12 || toInt(input[1])<-11){
			sysPrintString("Timezone values must be between -11 and +12\n", CB, CG, CR);
			return 1;
		}

		timeZone = toInt(input[1]);

		return 0;
	}
	else if(strcmp(input[0],"test") == 0) {
		if(words != 2) {
			sysPrintString("Wrong parameters: test receives one argument.\n", CB, CG, CR);
			return 1;
		}

		if(strcmp(input[1],"scheduler") == 0)
		    sysTestSuite(1);
		else if (strcmp(input[1],"ipc") == 0)
		    sysTestSuite(2);
    else if (strcmp(input[1], "mm") == 0)
        sysTestSuite(3);
    else if (strcmp(input[1],"all") == 0)
        sysTestSuite(0);
		else {
			sysPrintString("Wrong parameters: ", CB, CG, CR);
			sysPrintString(input[1], B, G, R);
			sysPrintString(" not recognized as an option.\n", CB, CG, CR);
		}
		return 0;
	}
	else if(strcmp(input[0],"contextSwitchDemo") == 0) {
		runContextSwitchDemo();
		return 0;
	}
	else if(strcmp(input[0],"foreground") == 0) {
		if(words != 2) {
			sysPrintString("Wrong parameters: foreground receives one argument.\n", CB, CG, CR);
			return 1;
		}

		foreground(input[1]);
		return 0;
	}
    else if(strcmp(input[0],"background") == 0) {
        if(words != 2) {
            sysPrintString("Wrong parameters: background receives one argument.\n", CB, CG, CR);
            return 1;
        }

        callFunction(input[1],1);
        return 0;
    }
	else if(strcmp(input[0],"prodConsDemo") == 0) {
    if(words!=1)
    {
			sysPrintString("No extra parameters for prodConsDemo.\n", CB, CG, CR);
			return 1;
    }else
    {
      prodConsDemo();
      return 0;
    }
  }
    else if(strcmp(input[0],"ps") == 0) {
        if(words!=1)
        {
            sysPrintString("Wrong parameters: ps receives no arguments.\n", CB, CG, CR);
            return 1;
        }
        listProcesses();
        return 0;

    }
	else {
		sysPrintString("Wrong input\n", CB, CG, CR);

		return 1;
	}

	return 1;
}

int verifyOperation(char * op)
{
  char * operationsName[4] = {"add", "subtract", "multiply", "divide"};
  for (int i = 0; i < 4; ++i)
  {
    if (strcmp(op, operationsName[i]) == 0)
    {
      return 1;
    }
  }
  return 0;
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

int calculateVerifications(int words, char* input1, char* input2, char* input3){
	if(verifyOperation(input1)==0 || isNum(input2)==2 || isNum(input3)==2){
		sysPrintString("Wrong parameters for calculate: Numbers must be integer\n", CB, CG, CR);
		return 0;
	}
	if(words!=4 || !isNum(input2) || !isNum(input3) ){
		//veryfing that there are four inputs and that the last two are numbers
		sysPrintString("Wrong parameters for calculate\n", CB, CG, CR);
		return 0;
	}
	return 1;
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
		sysPrintString("Wrong amount of parameters for plot command\n\
		Use command help for guidelines\n", CB, CG, CR);

		return 2;
	}

	for (int i = 1; i <= GRAPH_PARAMETERS; i++) {
		if (!isNum(input[i])) {
			sysPrintString("Wrong parameters passed to plot command\n\
			Use command help for guidelines\n", CB, CG, CR);

			return 2;
		}
	}

	graphMain(toFloat(input[1]), toFloat(input[2]), toFloat(input[3]));
	return 0;

}

pid_t getForegroundPID(){
	return foregroundPID;
}

char pipeBuffer[256]={0};

void pipeToShell(char * message, pid_t pid){
    int i=0;
    while(*(message+i) && i<256) *(pipeBuffer + i) = message[i++];
    while(i++<256) *(pipeBuffer + i) = 0;
}

void checkPipePrint(){
    if(*pipeBuffer){
        sysPrintString("\n",255,255,255);
        sysPrintString(pipeBuffer,255,255,255);
        sysPrintString("\n",255,255,255);
        int i=0;
        while(i++<256) *(pipeBuffer + i) = 0;
    }
}


void listProcesses(){
    sysGetProcesses(processes,processNames,processesAmount);

    sysPrintString("PID      SLEEPS      NAME\n",255,255,255);
    int i;
    for(i=0;i<processesAmount[0];i++){
        sysPrintInt(processes[i][0],255,255,255);
        sysPrintString("        ",255,255,255);
        sysPrintInt(processes[i][1],255,255,255);
        sysPrintString("        ",255,255,255);
        sysPrintString(processNames[i],255,255,255);
        sysPrintString("\n",0,0,0);
    }
}