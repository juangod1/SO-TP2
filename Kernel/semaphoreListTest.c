#include "include/testLib.h"
#include "include/semaphoreList.h"
#include "include/lib.h"
#include "include/videoDriver.h"

listEntry testinglistEntry=NULL;
int global_key = 3;
int global_different_key = 4;
int global_distinct_key = 5;
int global_value=1;

void static whenAddingAnElement()
{
	createlistEntry(global_key, global_value, &testinglistEntry);
}
void static thenElementIsAdded()
{
	if(testinglistEntry!=NULL){
		if(testinglistEntry->key==global_key)
		{
			ok();
		}
		else
		{
			fail("Expected key value: 3, found different number\n");
		}
	}
	else
	{
		fail("Expected non-null pointer, found null pointer\n");
	}
}


void static whenRemovingAnElement()
{
	removeListEntryByKey(global_key, &testinglistEntry);
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
	createlistEntry(global_key, global_value, &testinglistEntry);
}

void thenThereIsOnlyOneElement()
{
	if(listSize(&testinglistEntry)==1)
	{
		ok();
	}
	else
	{
		fail("Expected null pointer, found pointer\n");
	}
}

void givenAPreviousDifferentElement()
{
	createlistEntry(global_different_key, global_value, &testinglistEntry);
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
	createlistEntry(global_key, global_value, &testinglistEntry);
	createlistEntry(global_different_key, global_value, &testinglistEntry);
	createlistEntry(global_distinct_key, global_value, &testinglistEntry);
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

void static setConditionsBackToNormal()
{
	totalListRemove(&testinglistEntry);
}

void semaphoreListTestMain()
{
	//printString("Testing list addition...\n",0,0,255);
	testlistAddition();
	setConditionsBackToNormal();
	//printString("Testing list removal...\n",0,0,255);
	testlistRemoval();
	setConditionsBackToNormal();
	//printString("Testing two same key additions\n",0,0,255);
	testTwoSameKeyAdditions();
	setConditionsBackToNormal();
	//printString("Testing different additions\n",0,0,255);
	testDifferentAdditions();
	setConditionsBackToNormal();
	//printString("Testing existance after removal\n",0,0,255);
	testingExistanceAfterRemoval();
	setConditionsBackToNormal();

}
