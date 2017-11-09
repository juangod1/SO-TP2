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

float toFloat(const char * s) {
  float rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1;
      continue;
    };
    int d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    };
  };
  return rez * fact;
}
