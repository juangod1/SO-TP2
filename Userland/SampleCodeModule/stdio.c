#include "stdLib.h"
#include "mathLib.h"
#include "stdio.h"

/* Code taken from clc-wiki.net/wiki/C_standard_library:string.h:strcmp */
int strcmp(const char* s1, const char* s2){
	while(*s1 && (*s1==*s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int isNum(char * s) {
	int decimal_marks = 0;

	if (*s == '-') {
		s++;
	}

	if (!IS_DIGIT(*s)) {
		return 0;
	} else {
		s++;
	}

	while (*s != '\0') {
		if (!IS_DIGIT(*s)) {
			if (*s == '.' && decimal_marks < 1 && IS_DIGIT(*(s + 1))) {
				decimal_marks++;
			} else {
				return 0;
			}
		}

		s++;
	}

	return 1;
}

int toInt(char * string) {
	int length;
	int powerTo;
	int rta = 0;
	char * auxString = string;

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

float toFloat(char * string) {
	int int_length, decimal_length, total_length;
	int powerTo;
	float rta = 0;
	char * auxString = string;

	if (*string == '-') {
		string++;
	}

	int_length = subStrleng(string, '.');
	decimal_length = strleng(string + int_length);
	total_length = int_length + 1 + decimal_length;
	powerTo = int_length;


	for (int i = 0 ; i < total_length; i++) {
		int digit = *string - '0';

		if (i < int_length) {
			powerTo--;
			rta += ((float)digit * tenPow(powerTo));
		} else if (i > int_length && (i - (int_length + 1)) < decimal_length) {
			powerTo++;
			rta += ((float)digit / tenPow(powerTo));
		}

		string++;
	}

	return (*auxString == '-') ? -rta : rta;
}
