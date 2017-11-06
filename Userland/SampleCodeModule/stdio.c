
/* Code taken from clc-wiki.net/wiki/C_standard_library:string.h:strcmp */

int strcmp(const char* s1, const char* s2){
	while(*s1 && (*s1==*s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int isNum(char* s){
	while(*s != '\0'){
		if(*s<0 || *s>9){
			return 0;
		}
		s++;
	}
	return 1;
}

int strlength(const char* s){
	const char* p = s;
	while(*s) ++s;
	return s-p;
}
int toNum(char* string){
	int length = strlength(string);
	int powerTo = length-1;
	int rta=0;
	for(int i = 0 ; i < length ; i++){ 

		int n = *string-'0';
		rta += n*tenPow(powerTo);
		string++;
		powerTo--;
	}
	return rta;
}
