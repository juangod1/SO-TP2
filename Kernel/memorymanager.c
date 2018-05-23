#include "include/memorymanager.h"
void * heapBase = (void*)0x400000;

bookBlock myHeapInfo = NULL;//Hoja del memory manager
bookBlock myKernelBook = NULL;//Hoja del kernel
bookBlock heapBookBase =  NULL;//Primer hoja del libro
bookBlock myBookLastPage = NULL;;//Ultima hoja del libro

u_int64_t pageDirArray[NUM_OF_PAGES];
char pageStatusArray[NUM_OF_PAGES];
char memoryManagerBlocksStatusArray[NUM_OF_BBLOCKS];

//Inicializar mi heap y variables de entorno. Devuelve 1 cuando hay error, 0 cuando fue exitoso.
int initMemoryManager(){
	printString("Initializing memory manager... \n",TB,TG,TR);
	initPageDirArray();
	initMemoryManagerBlocksArray();

	bookBlock newBookBlock = (bookBlock) HEAP_START;
	memoryManagerBlocksStatusArray[0]=1;
	newBookBlock->owner = 0;//ID del mmBookBlock
	newBookBlock->brk = BBLOCK_SIZE; //Como esto esta escrito en la pagina que hace referencia, ya esta corrido.
	newBookBlock->base = popNewPage();
	newBookBlock->stack=NULL;
	newBookBlock->prev = NULL;
	newBookBlock->next = NULL;
	if(newBookBlock->base == NULL){
		memoryManagerBlocksStatusArray[0]=0;
		return 1;
	}
	myHeapInfo = newBookBlock;

	bookBlock newKernelBookBlock = (bookBlock) mm_malloc(BBLOCK_SIZE);
	newKernelBookBlock->owner = 1;//ID del kernelBookBlock
	newKernelBookBlock->brk = DBLOCK_SIZE;
	newKernelBookBlock->base = popNewPage();
	newKernelBookBlock->stack=NULL;
	newKernelBookBlock->prev = newBookBlock;
	newKernelBookBlock->next = NULL;

	if(newKernelBookBlock->base == NULL){
		mm_free(newKernelBookBlock);
		return 1;
	}
	dataBlock firstDataBlock = (dataBlock) newKernelBookBlock->base;
	firstDataBlock->size=0;
	firstDataBlock->next=NULL;
	firstDataBlock->free=0;

	myKernelBook = newKernelBookBlock;
	newBookBlock->next = newKernelBookBlock;

	heapBookBase = newBookBlock;
	myBookLastPage = newKernelBookBlock;
	return 0;
}

void initPageDirArray(){
	for(int i=0; i<NUM_OF_PAGES; i++){
		pageDirArray[i] = (u_int64_t)(HEAP_START + i * PAGE_SIZE);
		pageStatusArray[i]=0;
	}
}


void initMemoryManagerBlocksArray(){
	for(int i=0;i<NUM_OF_BBLOCKS;i++){
		memoryManagerBlocksStatusArray[i] = 0;
	}
}

//New stack for process
void* getStack(int pid){
	bookBlock newBookBlock = mm_malloc(BBLOCK_SIZE);
	if(newBookBlock == NULL){
		return NULL;
	}
	newBookBlock->owner = pid+2;
	newBookBlock->brk = 0;
	newBookBlock->base = popNewPage();
	newBookBlock->stack = (void*)((u_int64_t)(popReverseNewPage()) + PAGE_SIZE);//Corrido al final porque es stack
	newBookBlock->prev = myBookLastPage;
	newBookBlock->next = NULL;
	if(newBookBlock->base == NULL){
		mm_free(newBookBlock);
		return NULL;
	}
	*((int*)newBookBlock->base) = 0;//Seteo en NULL para que sepa que no hay bloque cargado.
	if(newBookBlock->stack == NULL){
		mm_free(newBookBlock);
		return NULL;
	}


	myBookLastPage->next = newBookBlock;
	myBookLastPage = newBookBlock;
	return newBookBlock->stack;
}

//Memory manager malloc
void* mm_malloc(size_t s){
	int i = 0;
	while(memoryManagerBlocksStatusArray[i] == 1 && i<NUM_OF_BBLOCKS){
		i++;
	}
	if(i==NUM_OF_BBLOCKS){
		return NULL;
	}
	memoryManagerBlocksStatusArray[i] = 1;
	return (myHeapInfo->base + (i*BBLOCK_SIZE));
}

//Memory manager Free
void mm_free(void* pointer){
	if(pointer == NULL)
		return;
	int i = ((uint64_t)pointer - (uint64_t)myHeapInfo->base)/BBLOCK_SIZE;
	memoryManagerBlocksStatusArray[i]=0;
}

//Kernel malloc
void * malloc(size_t s){
	dataBlock freeBlock = searchFreeBlock((dataBlock)myKernelBook->base, s);
	if(freeBlock == NULL){
		int brk = myKernelBook->brk;
		if((brk + s + DBLOCK_SIZE) >= PAGE_SIZE){
			printString("Fallo malloc\n",TB_FAIL,TG_FAIL,TR_FAIL);
			return (void *) 0x1500000;
		}
		myKernelBook->brk = (brk +s+DBLOCK_SIZE);

		//Nuevo dataBlock
		dataBlock newDataBlock =(dataBlock)(myKernelBook->base + brk);
		newDataBlock->size = s;
		newDataBlock->next = NULL;
		newDataBlock->free = 0;

		dataBlock lastDataBlock = getLastDataBlock((dataBlock) myKernelBook->base);
		lastDataBlock->next = newDataBlock;
		return (newDataBlock+1);
	} else {

		freeBlock->free=0;
		return (freeBlock+1);
	}
}

//Kernel free
void free(void *pointer)
{
	if (pointer == NULL) {
		return;
	}
	//TODO: una vez que genero los splits, tengo que hacer un metodo que pueda reunir los bloques
	dataBlock oldDataBlock = getDataBlock(pointer);
	oldDataBlock->free = 1;
}


//Syscall heapBase
void getMyHeapBase(dataBlock * db)
{
	int pid = getPid();
	pid+=2;

	bookBlock bookedBlock = searchBookedBlock(pid);
	if(bookedBlock == NULL){//Proceso no existe
		*db=NULL;
		return;
	}
	*db= bookedBlock->base;
	return;
}

//Syscall expandHeap
void expandHeap(dataBlock * db, size_t s)
{
	int pid = getPid();
	pid+=2;
	bookBlock bookedBlock = searchBookedBlock(pid);
	//Nadie hace expand sin tener una pagina asignada.
	int brk = bookedBlock->brk;

	if((brk + s) >= PAGE_SIZE){
		*db=NULL;
		return;
	}

	bookedBlock->brk = (brk + s);
	*db=bookedBlock->base +brk;
	return;
}

bookBlock searchBookedBlock(int id){
	bookBlock current = heapBookBase;
	while(current->owner != id){
		if(current->next == NULL){

			return NULL;
		}
		current = current->next;
	}
	return current;
}


dataBlock getDataBlock(void *pointer) {
  return (dataBlock)pointer - 1;
}

dataBlock getLastDataBlock(dataBlock first){
	dataBlock current = first;
	while(current->next != NULL){
		current = current->next;
	}
	return current;
}

dataBlock searchFreeBlock(dataBlock start, size_t size)
{
  dataBlock current = start;
  while (current!=NULL) {
		if(current->free && (current->size >= size))
			return current;
		current = current->next;
  }
  return current;
}

void * popNewPage(){
	int i = 0;
	while(pageStatusArray[i] && i<=NUM_OF_PAGES){
		i++;
	}
	if(i==NUM_OF_PAGES){
		return NULL;
	}
	pageStatusArray[i] = 1;
	return (void*) pageDirArray[i];
}

void* popReverseNewPage(){
	int i = NUM_OF_PAGES-1;
	while(pageStatusArray[i] && i>=-1){
		i--;
	}
	if(i==-1){
		return NULL;
	}
	pageStatusArray[i] = 1;
	return (void*) pageDirArray[i];
}

void dropBookPageForProcess(int pid){
	pid+=2;
	bookBlock bookBlockToDrop = searchBookedBlock(pid);
	(bookBlockToDrop->prev)->next = bookBlockToDrop->next;
	if(bookBlockToDrop->next != NULL){
	 	(bookBlockToDrop->next)->prev = bookBlockToDrop->prev;
	}else{
	myBookLastPage = bookBlockToDrop->prev;
	}

	dropPage((uint64_t)bookBlockToDrop->base);
	dropPage(((uint64_t)bookBlockToDrop->stack)-PAGE_SIZE);
	mm_free(bookBlockToDrop);
}


void dropPage(uint64_t dir){
	int i = 0;
	while(pageDirArray[i] != dir){
		i++;
	}

	pageStatusArray[i]=0;
}

//Print mm structure
void mmShow(){
	bookBlock current = heapBookBase;
	printString("Showing Heap Book. PID --> Base\n",TB,TG,TR);
	while(current!=NULL){
		printInt(current->owner,TB,TG,TR);
		printString(" --> ",TB,TG,TR);
		printHex((u_int64_t)current->base,TB,TG,TR);
		printString("\n",TB,TG,TR);
		if(current->owner != 0){
			printString("Showing Blocks. Size --> Status\n",TB,TG,TR);
			pbShow((dataBlock)current->base);
		}
		current = current->next;
		printString("--- \n",TB,TG,TR);
	}
}

void pbShow(dataBlock first){
	dataBlock current = first;
	while(current != NULL){
		printInt(current->size,TB,TG,TR);
		printString(" --> ",TB,TG,TR);
		printInt((u_int64_t)current->free,TB,TG,TR);
		printString("\n",TB,TG,TR);
		current = current -> next;
	}
}
