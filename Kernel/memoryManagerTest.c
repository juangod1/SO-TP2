#include "memoryManagerTest.h"
bookBlock mmBlock;
size_t size;
char* var;

void mmTester(){
  printString("Testing memory manager\n----------------------\n",255,0,0);

  testSuccessfullInit();
  testNoMallocBefore();
  testMaxSize();
  testMaxMinusOneSize();
  /*
  printInt(mmBlock->owner,255,255,255);
  printInt(getPid(),255,255,255);
  if(mmBlock->next == NULL)
    printInt(1,255,255,255);
  printString("\n",255,255,255);
  char* nombre ;
  nombre = (char*) malloc(8);

  if(mmBlock->next == NULL)
    printInt(1,255,255,255);
  if(mmBlock->next != NULL)
    printInt(2,255,255,255);

  printString("\n",255,255,255);

  int i;
  for(i=0;i<8;i++){
    *(nombre+i)=0;
  }

  nombre = "joaquin";

  printString(nombre,255,255,255);
  printString("\n",255,255,255);

  char* nombre2;
  nombre2 = (char*) malloc(6);

  nombre2 = "Pablo";

  printString(nombre2,255,255,255);
  printString("\n",255,255,255);

  printString(nombre,255,255,255);
  printString("\n",255,255,255);
  */
}

void testSuccessfullInit(){
  printString("Testing initialization --> ",255,255,255);
  givenAMemoryAddressBase();
  thenCheckMainBlockPid();
}

void testNoMallocBefore(){
  printString("Testing no malloc before tests --> ",255,255,255);
  givenAMemoryAddressBase();
  thenCheckFirstBookBlockNull();
}

void testMaxSize(){
  printString("Testing max size --> ",255,255,255);
  givenMaxSize();
  whenMallocSize();
  thenVarIsNull();
}

void testMaxMinusOneSize(){
  printString("Testing max minus one size --> ",255,255,255);
  givenMaxMinusOneSize();
  whenMallocSize();
  thenVarIsNotNull();
}

void givenAMemoryAddressBase(){
  mmBlock = (bookBlock) 0x400000;
}

void givenMaxSize(){
  size = 16384;
}

void givenMaxMinusOneSize(){
  size = 16383;
}

void whenMallocSize(){
  var = malloc(size);
}

void thenCheckMainBlockPid(){
  if(mmBlock->owner == 123){
    thenOk();
  }else{
    thenFailed();
  }
}

void thenVarIsNull(){
  if(var == NULL){
    thenOk();
  } else {
    thenFailed();
  }
}

void thenVarIsNotNull(){
  if(var != NULL){
    thenOk();
  } else {
    thenFailed();
  }
}

void thenCheckFirstBookBlockNull(){
  if(mmBlock->next == NULL){
    thenOk();
  } else {
    thenFailed();
  }
}



void thenOk(){
  printString("Success\n",0,255,0);
}

void thenFailed(){
  printString("Failed\n",0,0,255);
}
