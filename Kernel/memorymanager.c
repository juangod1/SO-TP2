#include "memorymanager.h"
void * heapBase = 0x400000; //Hay que verificar que tipo de dato conviene guardar el address
//Por el momento utilizo un entero para verificar un valor exacto ya que no se como hacer
//para asegurarme que este espacio inicialize en null o 0, de esta forma puedo reducirlo a
//un unico bit. Dejo 8 bytes para no perder la alineacion a palabra.

bookBlock heapBookBase =  NULL;//Referencia principal a mi cadena de registros

bookBlock myStorageCurrent = NULL;
bookBlock myStorageLast = NULL;
bookBlock myStorageBase = (bookBlock) 0x400000;//Este es mi heap

bookBlock searchBookedBlock(int id);
void * popNewPage();
//int getpid();

dataBlock getDataBlock(void *pointer);
dataBlock 	searchFreeBlock(dataBlock *last, size_t size);
dataBlock expandHeap(dataBlock* last, size_t size);
void *mymalloc(size_t size);
void myfree(void *pointer);
void *assignStack();
void *sbrk(size_t s);

//Tengo que tener un array con todas las direcciones de las paginas y de ahi voy sacandolas
//y volviendolas a poner. Al volverlas a poner las tengo que poner en 0 nuevamente
u_int64_t pageDirArray[NUM_OF_PAGES];

void initPageDirArray(){
	for(int i=0; i<NUM_OF_PAGES; i++){
		pageDirArray[i] = myStorageBase + i * PAGE_SIZE;
		pageStatusArray[i]=0;
	}
}


//Hay que definir un espacio de memoria para el stack y para el heap. El stack se va a ir asignando
//regularmente a continuacion del mismo cada vez que se ejecuta un nuevo programa.
//Por otro lado el heap estara en un espacio de memoria definido y se manejara con las funciones
//malloc para asignar y free para liberar.
//Fuente para el malloc https://danluu.com/malloc-tutorial/

//Problemas a lidiar:
//- Como ver si un programa esta tratando de utilizar un espacio de memoria que no le pertenece.

//Sacarlo cuando Juan suba el suyo.
int getpid(){
	return 0;
}

//Metodos de parciales
//Malloc otorga un espacio de memoria de x bytes
void *malloc(size_t s){
	//Si nunca fue inicializado el book keeping de las paginas, lo inicializo
	if(myStorageCurrent == NULL){
		bookBlock newBookBlock = myStorageBase;
		newBookBlock->owner = 3570;//Este es mi bloque elijamos un numero
		newBookBlock->brk = 0; //No estoy verificando que no caiga de pagina.
		newBookBlock->base = popNewPage();
		newBookBlock->next = NULL;
		if(newBookBlock->base == NULL){
			//No hay mas paginas disponibles (Esto no deberia pasar nunca en este caso porque es el primero)
			return NULL;
		}
		heapBookBase = newBookBlock;
		myStorageLast = myStorageBase;
		myStorageCurrent = myStorageBase+1;
		//Termine de armar el primero bloque que soy yo.
	}
	bookBlock bookedBlock = searchBookedBlock(getpid());
	if(bookedBlock == NULL){
		//No encontro ninguna pagina almacenada, hay que crear una nueva
		if((myStorageCurrent+sizeof(struct bookBlockStruct)) >= (myStorageBase+PAGE_SIZE))//Verifico que mi nuevo bloque no se caiga de mi pagina. Si queremos hay que agrandar el espacio de storage.
			return NULL;
		bookBlock newBookBlock = myStorageCurrent;
		newBookBlock->owner = getpid();
		newBookBlock->brk = s; //No estoy verificando que no caiga de pagina.
		newBookBlock->base = popNewPage();
		newBookBlock->next = NULL;
		if(newBookBlock->base == NULL){
			//No hay mas paginas disponibles (Esto no deberia pasar nunca en este caso porque es el primero)
			return NULL;
		}
		myStorageLast->next = newBookBlock;
		myStorageLast = myStorageCurrent;
		myStorageCurrent = myStorageCurrent+1;
		return newBookBlock->base;
	}
	else{
		//Al encontrarla me guardo el break anterior
		int brk = bookedBlock->brk;
		//Deberia verificar que tiene espacio en la pagina para la nueva magnitud
		//Aumento el brk
		if((brk + s) >= (bookedBlock->base+PAGE_SIZE)){//Se cae de la pagina
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
