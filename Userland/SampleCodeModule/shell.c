#include "shell.h"

static int R = DR;
static int G = DG;
static int B = DB;
static int isRunning = 1;
pid_t foregroundPID = 0;

char processNames[MAX_PROCESSES*MAX_PROCESS_NAME_LENGTH]={0};
int processesSleep[MAX_PROCESSES];
pid_t processesPID[MAX_PROCESSES];
int processesAmount[1];

void startShell(){
	sysPrintString("Shell initialized\n", CB, CG, CR);
	char string[MAX_WORD_LENGTH] = {0};
	char lastString[MAX_WORD_LENGTH] = {0};
	int counter = 0;
	char ch;

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
				callFunctionWrapper(string,1);
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

int callFunctionWrapper(char * string, int backgroundflag)
{
	char ** pipedFunctions;
	int pipeAmount = split(string, '|', &pipedFunctions);
	int words;
	char ** input =NULL;
	for(int i=0; i<pipeAmount; i++)
	{
		callFunction(pipedFunctions[i],backgroundflag, &input, &words);
		finalizeFunctionCall(input,words);
	}
	for(int i=0; i<pipeAmount; i++)
	{
		free(pipedFunctions[i]);
	}
	free(pipedFunctions);
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
		return setFontColor(input[1],&B,&G,&R);
	}
  else if (strcmp(input[0], "clear") == 0) {
    if(words > 2) {
      sysPrintString("No extra parameters for clear\n", CB, CG, CR);
      return 1;
    }
		return clear(words);
	}
	else if (strcmp(input[0], "calculate") == 0) {
		return calculateWrapper(words,input[1],input[2],input[3]);
	}
  else if (strcmp(input[0], "help") == 0) {
		if(words > 2) {
			sysPrintString("Too many parameters for help\n", CB, CG, CR);
			return 1;
		}
		return help(words, input);
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
    return 0;
	}
  else if (strcmp(input[0],"displayTime") == 0) {
		if(words != 1) {
			sysPrintString("No extra parameters for displayTime\n", CB, CG, CR);
			return 1;
		}
		return displayTime();
	}
  else if(strcmp(input[0],"setTimeZone") == 0) {
		if(words != 2) {
			sysPrintString("Wrong parameters: setTimeZone timezone\n", CB, CG, CR);
			return 1;
		}
		return setTimeZone(input[1]);
	}
	else if(strcmp(input[0],"test") == 0) {
		if(words != 2) {
			sysPrintString("Wrong parameters: test receives one argument.\n", CB, CG, CR);
			return 1;
		}
		return testModule(input[1]);
	}
	/*else if(strcmp(input[0],"contextSwitchDemo") == 0) {               ===========
		sysExecute(runContextSwitchDemo,"switcheroo");                      DEPRECATED
		return 0;                                                          ===========
	}*/
	else if(strcmp(input[0],"messageBoxDemo") == 0) {
		if(words!= 1)
		{
			sysPrintString("No extra parameters for messageBoxDemo.\n", CB, CG, CR);
			return 1;
		}
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
    }
    prodConsDemo();
    return 0;
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

int testModule(char * input1)
{
	if (strcmp(input1,"ipc") == 0)
			sysTestSuite(2);
	else if (strcmp(input1, "mm") == 0)
			sysTestSuite(3);
	else if (strcmp(input1,"all") == 0)
			sysTestSuite(0);
	else if (strcmp(input1,"md") == 0)
			sysTestSuite(4);
	else if (strcmp(input1,"pipe") == 0)
			sysTestSuite(5);
	else {
		sysPrintString("Wrong parameters: ", CB, CG, CR);
		sysPrintString(input1, B, G, R);
		sysPrintString(" not recognized as an option.\n", CB, CG, CR);
	}
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

void foreground(pid_t pid){
    //DEBUGPrintInt(pid,100,100,100);
    foregroundPID = pid;
}
