#include "time.h"
#include "naiveConsole.h"
static unsigned long ticks = 0;

void timer_handler() {
	ncPrintDec(ticks);
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}
