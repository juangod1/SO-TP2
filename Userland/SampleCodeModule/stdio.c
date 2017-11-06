
/* Code taken from clc-wiki.net/wiki/C_standard_library:string.h:strcmp */

int strcmp(const char* s1, const char* s2){
	while(*s1 && (*s1==*s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int isNum(char* s){
	while(*s != '\0'){
		if(*s<0 || *s>9){
			return 1;
		}
		s++;
	}
	return 0;
}
