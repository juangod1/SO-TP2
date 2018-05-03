//
// Created by juangod on 18/04/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "testLib.h"

void givenNothing()
{
}

void checkIsNotNull(void * pointer)
{
    if(pointer == NULL)
    {
        fail("Expected: a non null pointer, recieved: a null pointer");
    }
    else
    {
        ok();
    }
}

void checkStringsEqual(char* str1, char* str2)
{
    if(strcmp(str1, str2) != 0)
    {
        fail("Expected: two equal strings, recieved: two different strings");
    }
    else
    {
        ok();
    }
}

void thenSuccess()
{
    ok();
}

void ok()
{
    printString("    Ok!\n",0,255,0);
}

void fail(char * errorMsg)
{
    printString("    Failed\n",0,0,255);
    perror(errorMsg);
}

void notImplemented()
{
    perror("Not implemented.");
}