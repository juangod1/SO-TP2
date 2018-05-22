#include "lib.h"

void * memset(void * destination, int32_t c, uint64_t length)
{
	uint8_t chr = (uint8_t)c;
	char * dst = (char*)destination;

	while(length--)
		dst[length] = chr;

	return destination;
}

int memcmp(const char * destination, const char * source, uint8_t length)
{
	for(int i=0; i<length; i++)
	{
		if(*(destination+i)!=*(source+i))
		{
			return 1;
		}
	}
	return 0;
}


void * memcpy(void * destination, const void * source, uint64_t length)
{
	/*
	* memcpy does not support overlapping buffers, so always do it
	* forwards. (Don't change this without adjusting memmove.)
	*
	* For speedy copying, optimize the common case where both pointers
	* and the length are word-aligned, and copy word-at-a-time instead
	* of byte-at-a-time. Otherwise, copy by bytes.
	*
	* The alignment logic below should be portable. We rely on
	* the compiler to be reasonably intelligent about optimizing
	* the divides and modulos out. Fortunately, it is.
	*/
	//if((uint64_t)destination-(uint64_t)source<length && (uint64_t)destination>(uint64_t)source)
	//{
	//	return memcpyBackwards(destination, source, length);
	//}
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;

		for (i = 0; i < length / sizeof(uint32_t); i++)
			d[i] = s[i];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[i] = s[i];
	}

	return destination;
}

void * memcpyBackwards(void * destination, void * source, uint64_t length)
{
	uint64_t i;

	if ((uint64_t)destination % sizeof(uint32_t) == 0 &&
		(uint64_t)source % sizeof(uint32_t) == 0 &&
		length % sizeof(uint32_t) == 0)
	{
		uint32_t *d = (uint32_t *) destination;
		const uint32_t *s = (const uint32_t *)source;
		length/=sizeof(uint32_t);

		for (i = 0; i < length; i++)
			d[length-i-1] = s[length-i-1];
	}
	else
	{
		uint8_t * d = (uint8_t*)destination;
		const uint8_t * s = (const uint8_t*)source;

		for (i = 0; i < length; i++)
			d[length-i-1] = s[length-i-1];
	}

	return destination;
}

int strcmp(const char* s1, const char* s2){
	while(*s1 && (*s1==*s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char * intToString(int i){
	char * a = malloc(countDigits(i)+1);
	int count = 0;

	do {
		a[count++] = i%10+48;
	} while(i/=10);

	a[count] = '\0';
	return a;
}

int countDigits(int num){
	int dig = 1;
	while((num/=10) != 0) dig++;
	return dig;
}