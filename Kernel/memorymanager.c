#include "memorymanager.h"
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

struct dataBlock {
  size_t size;
  struct dataBlock *next;
  int free;
}dataBlock;

void * heapBase = NULL; //Hay que verificar que tipo de dato conviene guardar el address

dataBlock *getDataBlock(void *pointer);
dataBlock *searchFreeBlock(dataBlock **last, size_t size);
void *malloc(size_t size);
void free(void *pointer);
void *assignStack();

//Hay que definir un espacio de memoria para el stack y para el heap. El stack se va a ir asignando
//regularmente a continuacion del mismo cada vez que se ejecuta un nuevo programa.
//Por otro lado el heap estara en un espacio de memoria definido y se manejara con las funciones
//malloc para asignar y free para liberar.
//Fuente para el malloc https://danluu.com/malloc-tutorial/

//Problemas a lidiar:
//- Como ver si un programa esta tratando de utilizar un espacio de memoria que no le pertenece.

void main(int argc, char ** args)
{
}

dataBlock *getDataBlock(void *pointer) {
  return (struct dataBlock*)pointer - 1;
}

//Con este metodo se recorren los headers de cada bloque buscando que uno que cumpla con lo requerido
dataBlock *searchFreeBlock(dataBlock **last, size_t size)
{
  dataBlock *current = heapBase;
  while (current && !(current->free && current->size >= size)) {
    *last = current;
    current = current->next;
  }
  return current;
}

//Si no se encuentra un bloque que cumpla con lo requerido, se deberia hacer un sbrk()
//para generar nuevo espacio. 
dataBlock *expandHeap(dataBlock* last, size_t size)
{
  dataBlock *block;
  //Me devuelve el puntero a la base del heap
  block = sbrk(0);

  //Verifica que lo que estoy pidiendo va a entrar en mi nuevo heap.
  void *newBlock = sbrk(size + BLOCK_SIZE);
  assert((void*)block == request);

  //Si no alcanza el espacio
  if (request == (void*) -1) {
    return NULL; 
  }

  //Siempre que no sea el primer llamado, quiero conectar mi nuevo bloque a la cadena.
  if (last) {
    last->next = block;
  }
  block->size = size;
  block->next = NULL;
  block->free = 0;
  return block;
}

//Los bloques van a tener un bloque adelante y un bloque atras donde indican cuanto mide 
//y si esta siendo utilizado o no.
void *malloc(size_t size)
{
	dataBlock *block;
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
		dataBlock *last = heapBase;
		block = searchFreeBlock(&last, size);
		//Si no encuentro un bloque libre
		if (!block) {
	  		block = expandHeap(last, size);
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
void free(void *pointer) 
{
	//Se puede llamar con NULL por lo que lo verifico
	if (!pointer) {
	return;
	}

	// TODO: una vez que genero los splits, tengo que hacer un metodo que pueda reunir los bloques
	dataBlock* blockSpace = getDataBlock(pointer);
	assert(blockSpace->free == 0);
	blockPointer->free = 1;
}

//Asigna un espacio de memoria para que la aplicacion que lo necesita vaya utilizando para sus variables
void *assignStack(){
	
}