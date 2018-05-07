/* sampleCodeModule.c */
#include "stdLib.h"
#include "shell.h"
#include "mathLib.h"
#include "plotLib.h"
#include "contextSwitchDemo.h"

void shellWrapper();

int main()
{
	startShell();
	return 1;
}

void shellWrapper()
{
	startShell();
}
