#include <stdio.h>

#define MODULO 10007

int validateIndex(int k, int size) {
	if (k >= size) { 
		printf("No matrix with the given index\n");
		return 0;  
	}
	return 1;
}

int validateSizeOfMatrix(int k1, int k2, int *ql, int *qc)
{
	if(qc[k1] != ql[k2]) {
		printf("Cannot perform matrix multiplication\n");
		return 0;
	} else {
		if(ql[k1] != qc[k2] || ql[k2] != qc[k2]) {
			printf("Cannot perform matrix multiplication\n");
			return 0;
		}
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