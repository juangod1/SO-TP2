#include "memorymanager.h"






void * heapBase = NULL; //Hay que verificar que tipo de dato conviene guardar el address
//Por el momento utilizo un entero para verificar un valor exacto ya que no se como hacer 
//para asegurarme que este espacio inicialize en null o 0, de esta forma puedo reducirlo a 
//un unico bit. Dejo 8 bytes para no perder la alineacion a palabra.
int * heapBookStarted = (int*)0xFFFFFFFFFFFFEFFF;
void * heapBookBase = (void*)0xFFFFFFFFFFFFF008;

void * myHeapBase = (void*) 0x10100000;

void *malloc(size_t size);
void free(void *pointer);

bookBlock searchBookedBlock(int id);
void * popNewPage();
int getpid();

dataBlock getDataBlock(void *pointer);
dataBlock 	searchFreeBlock(dataBlock *last, size_t size);
dataBlock expandHeap(dataBlock* last, size_t size);
void *mymalloc(size_t size);
void myfree(void *pointer);
void *assignStack();
void *sbrk(size_t s);

//Tengo que tener un array con todas las direcciones de las paginas y de ahi voy sacandolas
//y volviendolas a poner. Al volverlas a poner las tengo que poner en 0 nuevamente
u_int64_t pageArray[5] = {0x10101000,0x10102000,0x10103000,0x10104000,0x10105000};
u_int8_t amountOfPagesRemaining  = 6;


//Hay que definir un espacio de memoria para el stack y para el heap. El stack se va a ir asignando
//regularmente a continuacion del mismo cada vez que se ejecuta un nuevo programa.
//Por otro lado el heap estara en un espacio de memoria definido y se manejara con las funciones
//malloc para asignar y free para liberar.
//Fuente para el malloc https://danluu.com/malloc-tutorial/

//Problemas a lidiar:
//- Como ver si un programa esta tratando de utilizar un espacio de memoria que no le pertenece.

int getpid(){
	return 0;
}
//Metodos de parciales
//Malloc otorga un espacio de memoria de x bytes
void *malloc(size_t s){
	//Si nunca fue inicializado el book keeping de las paginas, lo inicializo
	if(*heapBookStarted != 123){
		//Limpiar el espacio para el book y crear el primer nodo
		//Buscar como se hace correctamente
		//Crear nueva pagina para el proceso
		//En este caso, deberia primero asignar la pagina 1 al memory manager.
		bookBlock newBookBlock = myHeapBase;
		newBookBlock->owner = getpid();
		newBookBlock->brk = 0; //Esto es para proxima version
		newBookBlock->bookedHeapBase = popNewPage();
		if(newBookBlock->bookedHeapBase == NULL){
			//No hay mas paginas disponibles (Esto no deberia pasar nunca en este caso porque es el primero)
			return NULL;
		}
		*heapBookStarted = 123;
		return newBookBlock->bookedHeapBase;
	}
	bookBlock bookedBlock = searchBookedBlock(getpid());
	if(bookedBlock == NULL){
		//No encontro ninguna pagina almacenada, hay que crear una nueva
		bookBlock newBookBlock;
		newBookBlock->owner = getpid();
		newBookBlock->brk = 0; //Esto es para proxima version
		newBookBlock->bookedHeapBase = popNewPage();
		if(newBookBlock->bookedHeapBase == NULL){
			//No hay mas paginas disponibles (Esto no deberia pasar nunca en este caso porque es el primero)
			return NULL;
		}
		*heapBookStarted = 123;
		return newBookBlock->bookedHeapBase;
	}
	else{
		//Al encontrarla me guardo el break anterior
		int brk = bookedBlock->brk;
		//Deberia verificar que tiene espacio en la pagina para la nueva magnitud
		//Aumento el brk
		bookedBlock->brk += s;
		//Devuelvo el puntero a la pagina sumado el brk anterior
		return (bookedBlock->bookedHeapBase) + brk;
	}
}

bookBlock searchBookedBlock(int id){
	bookBlock current = (bookBlock)heapBookBase;
	while(current->owner != id){
		if(current->next == NULL){
			//No se encontro una pagina asociada al proceso
			return NULL;
		}
		current = current->next;
	}
	return current;
}

void * popNewPage(){
	//Tiene que verificar que le queda stock de paginas para asignar y manejarse como un stack
	//Por el momento solo devuelve una hoja 
	if(amountOfPagesRemaining == 0){
		return NULL;
	}
	u_int64_t newPage = pageArray[amountOfPagesRemaining-1];//Es menos uno por la correcion de posiciones
	amountOfPagesRemaining--;
	return (void*) newPage;
}



dataBlock getDataBlock(void *pointer) {
  return (dataBlock)pointer - 1;
}

//Con este metodo se recorren los headers de cada bloque buscando que uno que cumpla con lo requerido
dataBlock searchFreeBlock(dataBlock *last, size_t size)
{
  dataBlock current = (dataBlock)heapBase;
  while (current!=NULL && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

//Si no se encuentra un bloque que cumpla con lo requerido, se deberia hacer un sbrk()
//para generar nuevo espacio. 
dataBlock expandHeap(dataBlock* last, size_t size)
{
  dataBlock block;
  //Me devuelve el puntero a la base del heap
  block = sbrk(0);

  //Verifica que lo que estoy pidiendo va a entrar en mi nuevo heap.
  void *newBlock = sbrk(size + BLOCK_SIZE);
  //assert((void*)block == newBlock);

  //Si no alcanza el espacio
  if (newBlock == (void*) -1) {
    return NULL;
  }

  //Siempre que no sea el primer llamado, quiero conectar mi nuevo bloque a la cadena.
  if (*last) {
    (*last)->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  return block;
}

//Los bloques van a tener un bloque adelante y un bloque atras donde indican cuanto mide 
//y si esta siendo utilizado o no.
void *mymalloc(size_t size)
{
	dataBlock block;
	//ToDo: allignment

	//Tamano invalido
	if (size <= 0) 
	{
		return NULL;
	}

	//Primer llamado, se tiene que asignar el heap.
	if (!heapBase)
	{
		block = expandHeap(NULL, size);
		if (!block) 
			return NULL;
		heapBase = block;
	}
	else
	{
		dataBlock last = heapBase;
		block = searchFreeBlock(&last, size);
		//Si no encuentro un bloque libre
		if (!block) {
	  		block = expandHeap(&last, size);
	  		if (!block)
	    		return NULL;
		}
		else
		{
			//ToDo: blockSplitting
	  		block->free = 0;
		}
	}
	//Devuelvo el puntero al espacio que realmente esta libre, es decir, por delante de mi dataBlock
	//al estar casteado, el +1 itera el espacio que ocupa un blockData
	return(block+1);
}

//Tiene que recorrer los bloques y ver cambiar el bit de "uso" recursivamente para adelante y para atras
void myfree(void *pointer) 
{
	//Se puede llamar con NULL por lo que lo verifico
	if (!pointer) {
	return;
	}

	// TODO: una vez que genero los splits, tengo que hacer un metodo que pueda reunir los bloques
	dataBlock blockSpace = getDataBlock(pointer);
	//assert(blockSpace->free == 0);
	blockSpace->free = 1;
}

//Asigna un espacio de memoria para que la aplicacion que lo necesita vaya utilizando para sus variables
void *assignStack(){
	return NULL;	
}

//Mueve el break point de heap correspondiente y devuelve el puntero al mismo
void *sbrk(size_t s){
	return NULL;
}