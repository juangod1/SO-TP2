#include "shellFunctions.h"

static int timeZone = -3;

static int R = DR;
static int G = DG;
static int B = DB;

int displayTime()
{
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

int setFontColor(char * input, int * blue, int * green, int * red)
{
	if (strcmp(input, "red") == 0){
		//sysChangeScreenColors(B,G,R,255,0,0);
		R=255;
		B=0;
		G=0;
	}
	else if (strcmp(input, "green") == 0){
		//sysChangeScreenColors(B,G,R,0,255,0);
		R=0;
		B=0;
		G=255;
	}
	else if (strcmp(input, "blue") == 0){
		//sysChangeScreenColors(B,G,R,0,0,255);
		R=0;
		B=255;
		G=0;
	}
	else if (strcmp(input, "default") == 0){
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
  *blue=B;
  *green=G;
  *red=R;
	return 0;
}


int help(int words, char ** input)
{
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

int calculateWrapper(int words, char * input1, char * input2,char * input3)
{
	if (calculateVerifications(words, input1, input2, input3)) {
		int int2 = toInt(input2);
		int int3 = toInt(input3);


		int ans = calculate(input1, int2, int3);

		sysPrintString("Calculated: ", B, G, R);
		sysPrintInt(ans, B, G, R);
		sysPrintString("\n", B, G, R);
		return 0;
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

int setTimeZone(char * input1)
{

  if(toInt(input1)>12 || toInt(input1)<-11){
    sysPrintString("Timezone values must be between -11 and +12\n", CB, CG, CR);
    return 1;
  }

  timeZone = toInt(input1);

  return 0;
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
