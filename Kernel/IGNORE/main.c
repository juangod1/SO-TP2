#include "messaging.h"
#include "process1.h"
#include "process2.h"


int main()
{
  initializePostOffice();
  process1();
  process2();
  finalizePostOffice();

}
