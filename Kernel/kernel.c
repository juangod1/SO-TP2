#include "kernel.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x800000;
static void * const sampleDataModuleAddress = (void*)0x900000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{

	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);

	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main() {
  load_idt();
  initMemoryManager();
	initializeScreenBuffer();
  paintBackGround();
	resetScreenCoordinates();

	initializePostOffice();		//  Messaging system
	initializeTrafficControl();// Semaphore system
/*
 char * ptr2 = (char *)0x15002;
 char * ptr = (char *)0x15000;
 for (int i=0; i<100; i++){
	 switch(i%3)
	 {
		 case 0:
		 *(ptr+i)='z';
		 break;
		 case 1:
		 *(ptr+i)='y';
		 break;
		 case 2:
		 *(ptr+i)='x';
		 break;
	 }
 }
 printString(ptr,255,0,0);
 printString("\n",255,255,255);
 memcpy(ptr2,ptr,100);
 printString(ptr2,255,255,255);*/


	void (*module)();

	module = sampleCodeModuleAddress;
	module();
	while(1){
	}
	return 0;
}
