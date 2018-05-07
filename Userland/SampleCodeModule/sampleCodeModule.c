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
	//sysTestSuite(1);
	// startShell();
	//void (*shell_ptr)() = shellWrapper;
	sysExecute((void*)runContextSwitchDemo, name);
	return 1;
}

void shellWrapper()
{
	startShell();
}
