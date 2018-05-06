//
// Created by juangod on 18/04/18.
//
#include "include/lib.h"
#include "include/videoDriver.h"
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
    printString("    Ok!\n",TB_SUCCESS,TG_SUCCESS,TR_SUCCESS);
}

void fail(char * errorMsg)
{
    printString("    Failed\n",TB_FAIL,TG_FAIL,TR_FAIL);
    perror(errorMsg);
}

void notImplemented()
{
    perror("Not implemented.");
}
