/* sampleCodeModule.c */
#include "stdLib.h"
#include "shell.h"
#include "mathLib.h"
#include "plotLib.h"

void shellWrapper();

int main()
{
	char* name = "shell";
	//sysTestSuite(1);
	startShell();
	//void (*shell_ptr)() = &shellWrapper;
	//sysExecute(shell_ptr, &name);
	return 1;
}

void shellWrapper()
{
	startShell();
}
