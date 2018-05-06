#include "include/memorymanager.h"
void * heapBase = (void*)0x400000; //Hay que verificar que tipo de dato conviene guardar el address
//Por el momento utilizo un entero para verificar un valor exacto ya que no se como hacer
//para asegurarme que este espacio inicialize en null o 0, de esta forma puedo reducirlo a
//un unico bit. Dejo 8 bytes para no perder la alineacion a palabra.



bookBlock myHeapInfo = NULL;//Hoja del memory manager
bookBlock heapBookBase =  NULL;//Primer hoja del libro
bookBlock myBookLastPage = NULL;//Ultima hoja del libro

//Tengo que tener un array con todas las direcciones de las paginas y de ahi voy sacandolas
//y volviendolas a poner. Al volverlas a poner las tengo que poner en 0 nuevamente
u_int64_t pageDirArray[NUM_OF_PAGES];
char pageStatusArray[NUM_OF_PAGES];


//Hay que definir un espacio de memoria para el stack y para el heap. El stack se va a ir asignando
//regularmente a continuacion del mismo cada vez que se ejecuta un nuevo programa.
//Por otro lado el heap estara en un espacio de memoria definido y se manejara con las funciones
//malloc para asignar y free para liberar.
//Fuente para el malloc https://danluu.com/malloc-tutorial/

//Problemas a resolver:
//- Como ver si un programa esta tratando de utilizar un espacio de memoria que no le pertenece.


//Inicializar mi heap y variables de entorno. Devuelve 1 cuando hay error, 0 cuando fue exitoso.
int initMemoryManager(){
	initPageDirArray();
	//Levanto la primer pagina del book para mi. Como yo conozco esa direccion, ya la utilizo para guardar las cosas.
	bookBlock newBookBlock = (bookBlock) HEAP_START;
	newBookBlock->owner = 123;
	newBookBlock->brk = BBLOCK_SIZE; //Como esto esta escrito en la pagina que hace referencia, ya esta corrido.
	newBookBlock->base = popNewPage();
	newBookBlock->next = NULL;
	if(newBookBlock->base == NULL){
		//Esto no deberia pasar porque es el primer proceso.
		return 1;
	}
	myHeapInfo = newBookBlock;
	myBookLastPage = newBookBlock;//Simplemente para que el primer bloque del heapbook quede conectado a este, aunque este nunca se use.
	return 0;
}

void initPageDirArray(){
	for(int i=0; i<NUM_OF_PAGES; i++){
		pageDirArray[i] = (u_int64_t)(HEAP_START + i * PAGE_SIZE);
		pageStatusArray[i]=0;
	}
}

//Memory manager malloc
void* mm_malloc(size_t s){
	int brk = myHeapInfo->brk;
	if((brk + s) >= PAGE_SIZE){//Verifico que mi nuevo bloque no se caiga de mi pagina. Si queremos hay que agrandar el espacio de storage.
		return NULL;
	} else {
		myHeapInfo->brk += s;
		return myHeapInfo->base + brk;
	}
}

//Memory manager Free
void mm_free(){
}

//Metodos de parciales
//Malloc otorga un espacio de memoria de x bytes
void *malloc(size_t s){
	bookBlock bookedBlock = searchBookedBlock(getPid());
	if(bookedBlock == NULL){
		//No encontro ninguna pagina almacenada, hay que crear una nueva
		if(s >= PAGE_SIZE){//Pide mas de una pagina
			return NULL;
		}
		bookBlock newBookBlock = mm_malloc(BBLOCK_SIZE);
		if(newBookBlock == NULL){
			//No hay mas espacio para storage
			return NULL;
		}
		newBookBlock->owner = getPid();
		newBookBlock->brk = s; //Ya se sabe que no va a caer afuera de la pagina.
		newBookBlock->base = popNewPage();
		newBookBlock->next = NULL;
		if(newBookBlock->base == NULL){
			//No hay mas paginas disponibles (Esto no deberia pasar nunca en este caso porque es el primero)
			//Deberia hacer mm_free(newBookBlock)
			return NULL;
		}
		myBookLastPage->next = newBookBlock;//Conecto el anterior
		myBookLastPage = newBookBlock;//Cambio el ultimo bloque
		if(heapBookBase == NULL){
			heapBookBase = newBookBlock;
		}
		return newBookBlock->base;
	}
	else{
		//Al encontrarla me guardo el break anterior
		int brk = bookedBlock->brk;
		//Deberia verificar que tiene espacio en la pagina para la nueva magnitud
		//Aumento el brk
		if((brk + s) >= PAGE_SIZE){//Se cae de la pagina
			return NULL;
		}
		bookedBlock->brk += s;
		//Devuelvo el puntero a la pagina sumado el brk anterior
		return (bookedBlock->base) + brk;
	}
}

bookBlock searchBookedBlock(int id){
	bookBlock current = heapBookBase;
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
	//Recorre el array de estados para verificar hojas, luego la marca como ocupada y la devuelve.
	int i = 0;
	while(pageStatusArray[i]){//Cuando es 0 no entra, porque esta libre. Cuando es 1 entra porque esta ocupada y busca otra.
		i++;
	}
	if(i==NUM_OF_PAGES){//Si se paso significa que no hay mas paginas
		return NULL;
	}
	pageStatusArray[i] = 1;
	return (void*) pageDirArray[i];
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

//Free temporalmente deshabilitado
void free(void* pointer){
}

//Si no se encuentra un bloque que cumpla con lo requerido, se deberia hacer un sbrk()
//para generar nuevo espacio.
dataBlock expandHeap(dataBlock* last, size_t size)
{
  dataBlock block;
  //Me devuelve el puntero a la base del heap
  block = sbrk(0);

  //Verifica que lo que estoy pidiendo va a entrar en mi nuevo heap.
  void *newBlock = sbrk(size + DBLOCK_SIZE);
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

//Mueve el break point de heap correspondiente y devuelve el puntero al mismo
void *sbrk(size_t s){
	return NULL;
}
