#include "shell.h"
#include "stdLib.h"
#include "stdio.h"
#include "plotLib.h"
#include "mathLib.h"
#include "contextSwitchDemo.h"
#include "prodConsProblem.h"
#include "mmDemo.h"
#include "messageBoxDemo.h"

static int R = DR;
static int G = DG;
static int B = DB;
static int isRunning = 1;
static int timeZone = -3;
pid_t foregroundPID = 0;

char processNames[MAX_PROCESSES*MAX_PROCESS_NAME_LENGTH]={0};
int processesSleep[MAX_PROCESSES];
pid_t processesPID[MAX_PROCESSES];
int processesAmount[1];

mbd_t mbdescriptor;

void startShell(){
	sysPrintString("Shell initialized\n", CB, CG, CR);
	char string[MAX_WORD_LENGTH] = {0};
	char lastString[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char ch;

	int words;
	char ** input;

	sysPrintString("$> ",CB,CG,CR);

	while (isRunning) {
		if(checkIfForeground())
		sysGetChar(&ch);
		if(counter<MAX_WORD_LENGTH || ch == '\n'|| ch == '\b'){
		    if(checkIfForeground())
			sysWriteChar(ch, B, G, R);


			string[counter]=ch;
			(ch != 0) ? counter++ : counter;

			if (ch == '\n') {
				reset(lastString,strleng(lastString));
				copy(lastString,string,strleng(string)-1);
				callFunction(string,1, &input, &words);
				finalizeFunctionCall(input,words);
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
  sysExit();
}

int callFunction(char * buffer, int backgroundflag, char *** input_P, int * words_P)
{

	if (buffer == NULL){
		return 1;
	}


	removeLineBreak(buffer);

  *words_P=split(buffer, ' ',input_P);

	int words=*words_P;
	char ** input=*input_P;

	if (strcmp(input[0], "echo") == 0) {
		return echo(input, words);
	}
  else if (strcmp(input[0], "setFontColor") == 0) {
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
	}
  else if (strcmp(input[0], "clear") == 0) {
    if(words > 2) {
      sysPrintString("No extra parameters for clear\n", CB, CG, CR);
      return 1;
    }
		return clear(words);
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
	}
  else if (strcmp(input[0], "help") == 0) {
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
			else if(strcmp(input[1], "messageBoxDemo") == 0){
				sysPrintString(MESSAGEBOXDEMO_INS, B, G, R);
			}
			else if(strcmp(input[1], "plot") == 0){
				sysPrintString(PLOT_INS, B, G, R);
			}
      else if(strcmp(input[1], "runfg") == 0){
          sysPrintString(RUNFG_INS, B, G, R);
      }
      else if(strcmp(input[1], "test") == 0){
        sysPrintString(TEST_INS, B, G, R);
      }
      else if(strcmp(input[1], "mmDemo") == 0){
        sysPrintString(MMDEMO_INS, B, G, R);
      }
      else if(strcmp(input[1], "fg") == 0){
        sysPrintString(FOREGROUND_INS, B, G, R);
      }
      else if(strcmp(input[1], "prodConsDemo") == 0){
        sysPrintString(PRODCONS_INS, B, G, R);
      }
			else{
				sysPrintString("Not a valid command\n",CB,CG,CR);
			}
		}
		else{
			sysPrintString(helpIns, B, G, R);
		}

		return 0;
	}
  else if (strcmp(input[0], "exit") == 0 ) {
		if (words != 1) {
			sysPrintString("No extra parameters for exit\n", CB, CG, CR);

			return 1;
		}
		sysClear();
		sysPrintString("See you soon", CB, CG, CR);

		isRunning = 0;

		return 0;
	}
  else if (strcmp(input[0], "plot") == 0) {
		if (words != (GRAPH_PARAMETERS + 1)) {
			sysPrintString("Wrong amount of parameters for plot command\n\
			Use command help for guidelines\n", CB, CG, CR);

			return 2;
		}

		return graph(input[1], input[2], input[3]);
	}
  else if (strcmp(input[0], "mmDemo") == 0) {
    if(words!= 1)
    {
			sysPrintString("No extra parameters for mmDemo\n", CB, CG, CR);

			return 1;
    }
    sysClear();
		mmDemo();
		sysClear();
    //sysClear();
    return 0;
	}
  else if (strcmp(input[0],"displayTime") == 0) {
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
	}
  else if(strcmp(input[0],"setTimeZone") == 0) {
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
		else if (strcmp(input[1],"ipc") == 0)
		    sysTestSuite(2);
    else if (strcmp(input[1], "mm") == 0)
        sysTestSuite(3);
    else if (strcmp(input[1],"all") == 0)
        sysTestSuite(0);
		else if (strcmp(input[1],"md") == 0)
			  sysTestSuite(4);
		else if (strcmp(input[1],"pipe") == 0)
			  sysTestSuite(5);
		else {
			sysPrintString("Wrong parameters: ", CB, CG, CR);
			sysPrintString(input[1], B, G, R);
			sysPrintString(" not recognized as an option.\n", CB, CG, CR);
		}
		return 0;
	}
	/*else if(strcmp(input[0],"contextSwitchDemo") == 0) {               ===========
		sysExecute(runContextSwitchDemo,"switcheroo");                      DEPRECATED
		return 0;                                                          ===========
	}*/
	else if(strcmp(input[0],"messageBoxDemo") == 0) {
		messageBoxDemoMain();
		return 0;
	}
	else if(strcmp(input[0],"fg") == 0) {
		if(words != 2) {
			sysPrintString("Wrong parameters: foreground receives one argument.\n", CB, CG, CR);
			return 1;
		}

		foreground(toInt(input[1]));
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
  else if(strcmp(input[0],"testBackgroundProcess") == 0) {
    if(words>1)
    {
        sysPrintString("Wrong parameters: backgroundProcess receives no arguments.\n", CB, CG, CR);
        return 1;
    }
    int pid = sysExecute(backgroundProcessRun,"bg process test");
    if(!backgroundflag)
    	setForeground(pid);
      return 0;
  }
  else if(strcmp(input[0],"runfg") == 0) {
      if(words<2)
      {
          sysPrintString("Wrong parameters: runfg.\n", CB, CG, CR);
          return 1;
      }
			sysPrintString("DEPRECATED\n",CB,CG,CR);
      //callFunction(input[1],0);
      return 0;
  }
	else {
		sysPrintString("Wrong input\n", CB, CG, CR);

		return 1;
	}
}

void finalizeFunctionCall(char ** input, int words)
{
	for(int i=0; i<words; i++)
	{
		free(input[i]);
	}
	free(input);
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

int echo(char ** input, int words)
{
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

int graph(char * input1, char* input2, char * input3)
{
	if (!isNum(input1) ||!isNum(input1) ||!isNum(input1)) {
		sysPrintString("Wrong parameters passed to plot command\n\
		Use command help for guidelines\n", CB, CG, CR);
		return 2;
	}

	graphMain(toFloat(input1), toFloat(input2), toFloat(input3));
	return 0;

}

pid_t getForegroundPID(){
	return foregroundPID;
}

void listProcesses(){
    sysGetProcesses(processesPID,processesSleep,processNames,processesAmount);
    char * auxPtr=processNames;
    sysPrintString("PID      SLEEPS      NAME\n",255,255,255);
    int i;
    for(i=0;i<processesAmount[0];i++){
        sysPrintInt(processesPID[i],255,255,255);
        sysPrintString("        ",255,255,255);
        sysPrintInt(processesSleep[i],255,255,255);
        sysPrintString("        ",255,255,255);
        sysPrintString(auxPtr,255,255,255);
        sysPrintString("\n",0,0,0);
        auxPtr+=MAX_PROCESS_NAME_LENGTH;
    }
    reinitializeProcessNameBuffer();
}
void reinitializeProcessNameBuffer()
{
  char * auxPtr=processNames;
  for(int i=0; i<MAX_PROCESSES*MAX_PROCESS_NAME_LENGTH; i++)
  {
    *(auxPtr+i)=0;
  }
}

void setForeground(pid_t pid){
    foregroundPID = pid;
}

void backgroundProcessRun()
{
    int i,j,k;
    char ch;
    while(1) {
        for (i=1;i<256;i=i+30) {
            for (j=1;j<256;j=j+30) {
                for (k=1;k<256;k=k+30) {
                    sysGetChar(&ch);
                    if(ch=='\n')
						sysExit();
                    sysPrintString("Hello, i am a background process. Press ENTER to leave. Enjoy the RGB magic.\n", i, j, k);
                }
            }
        }
    }
}

void foreground(pid_t pid){
    //DEBUGPrintInt(pid,100,100,100);
    foregroundPID = pid;
}
