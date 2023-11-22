/*
realloc.c
v1.0

gcc realloc.c Matrix.c 

*/

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main() {

    int k;
   	char m1[] = "11 12 13 14";
	int *a = stringToVector(m1, &k);

	printVectorAddr(a,k);

	int *b;
	b = realloc(a, (10) * sizeof(int));
	//allocate memory at address b;
	//copies in at the addres b elements from address a;
	//frees the memory used by a
	//adress of a should no loger used;

	printVectorAddr(b,10);
	printVectorAddr(a,10);

	a = b;
	printVectorAddr(a,10);

    b = resizeVector(b,10,12);
   	printVectorAddr(b,12);


}
