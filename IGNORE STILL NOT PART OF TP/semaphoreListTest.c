#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "testlib.h"
#include "semaphoreList.h"

listEntry testinglistEntry=NULL;
int global_key = 3;
int global_different_key = 4;
int global_distinct_key = 5;

void whenAddingAnElement()
{
	createlistEntry(global_key, &testinglistEntry);
}
void thenElementIsAdded()
{
	if(testinglistEntry!=NULL){
		if(testinglistEntry->key==global_key)
		{
			ok();
		}
		else
		{
			char * errorStr=NULL;
			sprintf(errorStr, "Expected key value: %d, found: %d\n", global_key, testinglistEntry->key);
			fail(errorStr);
		}
	}
	else
	{
		fail("Expected non-null pointer, found null pointer\n");
	}
}


void whenRemovingAnElement()
{
	removelistEntry(global_key, &testinglistEntry);
}
void thenItemisRemoved()
{
	if(testinglistEntry==NULL)
	{
		ok();
	}
	else
	{
		fail("Expected null pointer found pointer\n");
	}
}

void givenAPreviousEqualElement()
{
	createlistEntry(global_key,&testinglistEntry);
}

void thenThereIsOnlyOneElement()
{
	if(listSize(&testinglistEntry)==1)
	{
		ok();
		removelistEntry(3, &testinglistEntry);
	}
	else
	{
		fail("Expected null pointer, found pointer\n");
	}
}

void givenAPreviousDifferentElement()
{
	createlistEntry(global_different_key, &testinglistEntry);
}

void thenThereIsTwoElements()
{
	if(listSize(&testinglistEntry)==2)
	{
		ok();
	}
	else
	{
		fail("Expected size 2, found different size");
	}
}
void givenThreeDifferentElements()
{
	createlistEntry(global_key, &testinglistEntry);
	createlistEntry(global_different_key, &testinglistEntry);
	createlistEntry(global_distinct_key, &testinglistEntry);
}
void thenTheRemovedElementIsRemoved()
{
	if(!listContains(3, &testinglistEntry))
	{
		ok();
	}
	else
	{
		fail("Expected list not to contain key 3, found list contains key 3");
	}
}

void thenTheOtherElementsRemain()
{
	if(listContains(4, &testinglistEntry) && listContains(5, &testinglistEntry))
	{
		ok();
	}
	else
	{
		fail("Expected list to contain keys 4 and 5, found list not to contain either 4 or 5");
	}
}

void testlistAddition()
{
	whenAddingAnElement();
	thenElementIsAdded();
}
void testlistRemoval()
{
	whenRemovingAnElement();
	thenItemisRemoved();
}
void testTwoSameKeyAdditions()
{
	givenAPreviousEqualElement();
	whenAddingAnElement();
	thenThereIsOnlyOneElement();
}
void testDifferentAdditions()
{
	givenAPreviousDifferentElement();
	whenAddingAnElement();
	thenThereIsTwoElements();
}
void testingExistanceAfterRemoval()
{
	givenThreeDifferentElements();
	whenRemovingAnElement();
	thenTheRemovedElementIsRemoved();
	thenTheOtherElementsRemain();
}

int main()
{
	printf("Testing list addition...\n");
	testlistAddition();
	printf("Testing list removal...\n");
	testlistRemoval();
	printf("Testing two same key additions\n");
	testTwoSameKeyAdditions();
	printf("Testing different additions\n");
	testDifferentAdditions();
	printf("Testing existance after removal");
	testingExistanceAfterRemoval();

}