/* sampleCodeModule.c */
#include "stdLib.h"
#include "shell.h"

extern void sysCall(uint64_t edi, uint64_t esi, uint64_t edx, uint64_t ecx);

int main() {

	/*int array[30];
	sysGetTime(array);
	sysPrintInt(array[2],255,255,255);
	sysPrintInt(array[1],255,255,255);*/

	startShell();

	return 1;
}
