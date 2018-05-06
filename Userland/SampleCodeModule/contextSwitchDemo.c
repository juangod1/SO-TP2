#include "stdio.h"
#include "stdLib.h"

int (*child_func)();
int (*func2)();
int (*func3)();
int (*func4)();
int (*func5)();

void childProcessFunction();
void f2();
void f3();
void f4();
void f5();

void runContextSwitchDemo()
{
    sysPrintString("Hello, I am the parent process.\n",0,255,255);
    char* name2 = "secondProcess";
    child_func = &childProcessFunction;
    sysExecute(child_func, name2);
}


void childProcessFunction()
{
    func2 = &f2;
    sysPrintString("Hello, I am the child process.\n",0,255,255);
    char* name2 = "thirdProcess";
    sysExecute(func2, &name2);
    sysPrintString("2nd process second print.\n",255,255,255);
    
}

void f2(){
    func3 = &f3;
    char* name3 = "fourthProcess";
    sysPrintString("Hello, I am the 3rd process.\n",255,255,255);
    sysExecute(func3, &name3);
    sysPrintString("3rd process second print.\n",255,255,255);
}


void f3(){
    func4 = &f4;
    sysPrintString("Hello, I am the 4th process.\n",255,255,255);
    char* name4 = "fourthProcess";
    sysExecute(func4, &name4);
    sysPrintString("3rd process second print.\n",255,255,255);
}


void f4(){
    func5 = &f5;
    sysPrintString("Hello, I am the 5th process.\n",255,255,255);
    char* name5 = "fifthProcess";
    sysExecute(func5, &name5);
    sysPrintString("3rd process second print.\n",255,255,255);
}


void f5(){
    sysPrintString("Hello, I am the 6th process.\n",255,255,255);
}