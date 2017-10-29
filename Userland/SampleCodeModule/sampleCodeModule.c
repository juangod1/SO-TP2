/* sampleCodeModule.c */
#include "stdLib.h"

extern void sysCall(int edi, int esi, int edx, int ecx);

int main() {

	char array[80];

	sysReadInput(array);

	sysPrintString(12,array[2]);

	return 1;
}
