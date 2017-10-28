#include <time.h>
#include <stdint.h>
#include "keyboardDriver.h"

static void int_20();

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
