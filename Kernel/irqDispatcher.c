#include <time.h>
#include <stdint.h>
#include "keyboardDriver.h"

void irqDispatcher(uint64_t irq) {
	switch (irq) {
		case 0:
			timer_handler();
			break;
		case 1:
			keyboard_handler();
			break;
	}
	return;
}
