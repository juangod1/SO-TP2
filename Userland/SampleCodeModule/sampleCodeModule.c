/* sampleCodeModule.c */
#include "stdLib.h"

extern void sysCall(uint64_t edi, uint64_t esi, uint64_t edx, uint64_t ecx);

int main() {


	sysPrintString(6,"aasdfadsfgasg");
	sysNewLine();
	sysPrintString(8,"newline");

	return 1;
}
