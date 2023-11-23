#include <stdio.h>

#define MODULO 10007

int validateIndex(int k, int size) {
	if (k >= size) { 
		printf("No matrix with the given index\n");
		return 0;  
	}
	return 1;
}

int validateSizeOfMatrix(int k1, int k2, int *l, int *c)
{
	if(c[k1] != l[k2]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	}
	return 1;
}

int moduloPositive(int x) {
    int r = x ;

	if (r > MODULO) {	
		r = r % MODULO;
	}

	if (r < -MODULO) {
		r = r % MODULO;
    	if (r < 0) r = r + MODULO;
	}
	return r;
}