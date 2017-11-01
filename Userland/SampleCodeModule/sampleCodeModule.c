/* sampleCodeModule.c */
#include "stdLib.h"

extern void sysCall(int edi, int esi, int edx, int ecx);

int main() {


	sysPrintString(6,"aasdfadsfgasg");
	sysNewLine();
	sysPrintString(8,"newline");

	return 1;
}
