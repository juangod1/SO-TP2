/* sampleCodeModule.c */
#include "stdLib.h"
#include "shell.h"
#include "mathLib.h"
#include "plotLib.h"

extern void sysCall(uint64_t edi, uint64_t esi, uint64_t edx, uint64_t ecx);

int main() {
	
	startShell();

	return 1;
}
