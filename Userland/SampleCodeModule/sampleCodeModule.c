/* sampleCodeModule.c */

extern void sysCall(int edi, int esi, int edx, int ecx);

int main() {

	sysCall(1,4,"This is a syscall example.",0);

	return 1;
}
