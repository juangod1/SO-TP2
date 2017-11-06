#include "mathLib.h"

float absFloat(float x) {
	return x >= 0.001 ? x : -x;
}


int fx(int x, int a, int b, int c) {
	return (a * x * x) + (b * x) + c;
}

float babylonianSqrt(int n, float S, float x0) {
	if (n <= 0)
		return x0;

	return (babylonianSqrt(n - 1, S, x0) + (S / babylonianSqrt(n - 1, S, x0))) / 2;
}

float sqrt(float S) {
	if (S <= -0.001) {
		// It could throw an exception regarding the sqrt of a negative number
		return -1;
	}

	int n = 6; // Arbitrary value for the number of iterations

	return babylonianSqrt(n, S, S / 2);
}

int add(int x, int y) {
	return x + y;
}

int subtract(int x, int y) {
	return x - y;
}

int multiply(int x, int y) {
	return x * y;
}

int divide(int x, int y) {
	return x / y;
}

int tenPow(int num){
	if(num==0){
		return 1;
	}
	return 10*tenPow(--num);
}