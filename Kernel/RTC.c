#include "RTC.h"
#include "videoDriver.h"

void printTime(uint8_t color){
  int hours = getHoursRTC();
  int mins = getMinutesRTC();

  printInt(color,hours);
  printChar(color,':');
  printInt(color,mins);
}
