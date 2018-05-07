/* sampleCodeModule.c */
#include "stdLib.h"
#include "shell.h"
#include "mathLib.h"
#include "plotLib.h"
#include "contextSwitchDemo.h"

void shellWrapper();

int main()
{
	char* name = "shell";
	sysExecute((void*)startShell, &name);
	return 1;
}

void shellWrapper()
{
	startShell();
}
