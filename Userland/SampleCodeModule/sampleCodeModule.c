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
	char ** buff;
	sysMalloc(buff,6);
	memcpy(*buff,name,6);
	sysExecute((void*)startShell, *buff);
	return 1;
}

void shellWrapper()
{
	startShell();
}
