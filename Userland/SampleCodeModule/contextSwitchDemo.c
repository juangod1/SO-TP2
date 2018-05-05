#include "stdio.h"
#include "stdLib.h"

int (*child_func)();

void childProcessFunction();

void runContextSwitchDemo()
{
    sysPrintString("Hello, I am the parent process.\n",0,255,255);
    child_func = &childProcessFunction;
    sysExecute(child_func);
}


void childProcessFunction()
{
    sysPrintString("Hello, I am the child process.\n",0,255,255);
    sysPrintString("My process id is:",0,255,255);
    sysPrintString("My process id is:",0,255,255);
    int pid = getPid();
    sysPrintInt(pid,0,0,0);
    sysPrintString("\n",0,0,0);
}
