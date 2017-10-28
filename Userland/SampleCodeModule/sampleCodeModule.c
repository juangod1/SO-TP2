/* sampleCodeModule.c */
#include "stdLib.h"

extern void sysCall(int edi, int esi, int edx, int ecx);

int main() {

	int array[6];

	sysGetTime(array);

	sysPrintInt(12,array[2]-3);
	sysPrintString(12,':');
	sysPrintInt(12,array[1]);
	char buffer[80];
	sysNewLine();
	sysPrintString(2,"string");
	sysReadInput(buffer);
	sysPrintString(4,buffer);
	return 1;
}
