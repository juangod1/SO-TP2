#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include "interrupts.h"
#include "videoDriver.h"
#include "idtLoader.h"
#include "stdio.h"
#include "memorymanager.h"
#include "include/schedulerTest.h"
#include "include/messaging.h"
#include "include/semaphoreList.h"

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
  paintBackGround();
	resetScreenCoordinates();
  initMemoryManager();

	initializePostOffice();		//  Messaging system
	initializeTrafficControl();// Semaphore system

	void (*module)();
	
	module = sampleCodeModuleAddress;
	module();
	while(1){
	}
	return 0;
}
