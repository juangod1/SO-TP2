#include "mmDemo.h"
#include "stdLib.h"
#include "shell.h"


void mmDemo()
{

  sysPrintString("Welcome to the Memory manager Demo, press any key to continue.\n", CB,CG,CR);
  char c=0;
  while(c==0)
  {
    sysGetChar(&c);
  }
  sysPrintString("Press any key to display Memory manager status.\n", CB,CG,CR);
  c=0;
  while(c==0)
  {
    sysGetChar(&c);
  }
  sysTestSuite(3);
  sysPrintString("The previous print displays all data blocks belonging to each page, each process is asigned a page. Page 0 for the memoryManager, 1 for the kernel and followed by the user land processes.\n\
The first integer is the size of the block in bytes, the bit next to it informs if the block is freed.\n\
Press any key to continue\n", CB,CG,CR);
  c=0;
  while(c==0)
  {
    sysGetChar(&c);
  }
  void * ptr=malloc(100);
  sysPrintString("A block of size 100 was alloc'd. FIND IT!\n\
Press any key to display Memory manager status.\n", CB,CG,CR);
  c=0;
  while(c==0)
  {
    sysGetChar(&c);
  }
  c=0;
  sysTestSuite(3);
  sysPrintString("Press any key to free the block.\n", CB,CG,CR);
  while(c==0)
  {
    sysGetChar(&c);
  }
  c=0;
  free(ptr);
  sysPrintString("The block of size 100 was free'd. Notice the change in status.\n\
Press any key to display Memory manager status.\n", CB,CG,CR);
  while(c==0)
  {
    sysGetChar(&c);
  }
  c=0;
  sysTestSuite(3);
  sysPrintString("Created processes will have their own data block status table.\n\
Press any key to create a process and have it to alloc 50 bytes.\n", CB,CG,CR);
  while(c==0)
  {
    sysGetChar(&c);
  }
  c=0;
  sysExecute(childMMDemo,"Child MM Demo");
  sysPrintString("Press any key to exit the process and print the status.\n", CB,CG,CR);
  while(c==0)
  {
    sysGetChar(&c);
  }
  c=0;
  sysTestSuite(3);
  sysPrintString("Hope you enjoyed the memory manager demo!.", CB,CG,CR);
  sysPrintString("HAVE FUN CODING!.\n",255,0,255);
  sysPrintString("Press any key to head back to the shell.\n", CB,CG,CR);
  while(c==0)
  {
    sysGetChar(&c);
  }
}

void childMMDemo()
{
  malloc(50);
  sysTestSuite(3);
  sysExit();
}
