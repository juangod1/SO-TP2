/* sampleCodeModule.c */
#include "stdLib.h"
#include "shell.h"
#include "mathLib.h"
#include "plotLib.h"
#include "contextSwitchDemo.h"

void shellWrapper();

void b();
void r();

int main()
{
	//sysExecute(startShell,"Shell");
	startShell();
	return 1;
}

void shellWrapper()
{
	startShell();
}

void b(){
    sysExecute(r,"reddy");
    while(1)
        sysPrintString("b",255,0,0);
}

void r(){
    while(1)
        sysPrintString("r",0,0,255);
}
