/* sampleCodeModule.c */
#include "stdLib.h"

extern void sysCall(uint64_t edi, uint64_t esi, uint64_t edx, uint64_t ecx);

int main() {

	int array[30];
	sysGetTime(array);
	sysPrintInt(2,array[2]);
	sysPrintInt(2,array[1]);

	return 1;
}
