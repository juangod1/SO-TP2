#include "stdLib.h"

/* Code taken from clc-wiki.net/wiki/C_standard_library:string.h:strcmp */
int strcmp(const char* s1, const char* s2){
	while(*s1 && (*s1==*s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int isNum(char* s) {
	if (*s == '-') {
		s++;
	}

	while (*s != '\0') {
		if ((*s - '0') < 0 || (*s - '0') > 9) {
			return 0;
		}

		s++;
	}

	return 1;
}

int toNum(char* string) {
	int length;
	int powerTo;
	int rta = 0;
	char* auxString = string;

	if (*string == '-') {
		string++;
	}

	length = strleng(string);
	powerTo = length - 1;

	for (int i = 0 ; i < length ; i++) {
		int n = *string - '0';
		rta += n * tenPow(powerTo);
		string++;
		powerTo--;
	}

	return (*auxString == '-') ? -rta : rta;
}
