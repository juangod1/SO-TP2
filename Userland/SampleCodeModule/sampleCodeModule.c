/* sampleCodeModule.c */
#include "stdLib.h"
#include "shell.h"
#include "mathLib.h"
#include "plotLib.h"
#include "contextSwitchDemo.h"
#include "prodConsProblem.h"
void shellWrapper();

void b();
void r();

int main()
{
	//startShell();
	sysExecute(startShell,"Shell");
	return 1;
}

void shellWrapper()
{
	startShell();
}