#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

// printCollection (collection, size, linesvector, columnsvector)
void printCollection(int ***a, int z, int *l, int *c)
{
    printf("printCollection /%d/\n", z);
	int i,j,k;
	for(k = 0; k < z; k++) {
		printf("#%d\n",k);
		for (i = 0; i < l[k]; i++)
		{
			for (j = 0; j < c[k]; j++){
				printf("%3d ", a[k][i][j]);
			}
			printf("\n");

		}
	}
}

// freeCollection(collection, size, linesvector, columnsvector)
void freeCollection(int ***a, int z, int *l, int *c)
{
    printf("freeCollection /%d/\n", z);
	int i,j,k;
	for(k = 0; k < z; k++) {
		for (i = 0; i < l[k]; i++)
		{
			free(a[k][i]);
		}
		free(a[k]);
	}
	free(a);
}

// newcollection = addMatrixtoCollection(collection, size, matrix, index, lines, columns)
int*** addMatrixtoCollection(int*** q, int* z, int* ql, int* qc, int** b, int l, int c)
{
    printf("addMatrixtoCollection [%d] [%d x %d]\n", *z, l, c);
	int ***a;
	int i,j,k;
	int nw = *z+1;
	ql[*z]=l;
	qc[*z]=c;
	a = malloc(nw * sizeof(int**));
	for (k = 0; k < nw; k++) {
		a[k]=malloc(ql[k] * sizeof(int*));
		for (i = 0; i < ql[k]; i++) {
			a[k][i] = malloc(qc[k] * sizeof(int));
				for (j = 0; j < qc[k]; j++){
					if (k < *z) {
						a[k][i][j] = q[k][i][j];
						}
					else {a[k][i][j]=b[i][j];}
				}
		}
	}
	freeCollection(q,*z,ql,qc);
	*z = nw;
	return a;
}

// resize = resizeCollectionCapacity(collection, size, newsize, linesvector, columnsvector)
int*** resizeCollectionCapacity(int ***w, int z, int nz, int *l, int *c) 
{
    printf("resizeCollection %d-->%d\n",z,nz);
    
    int ***a = malloc(nz * sizeof(int**));
	int i;
	int lz = z;
	int kz = 0;
	if (z > nz) lz = nz;

	for (i=0; i<lz; i++ ) 
		a = addMatrixtoCollection(a, &kz, l, c, w[i], l[i],c[i]);

	freeCollection(w,z,l,c);

    return a;
}

int*** replaceMatrixinCollection(int*** q, int nw, int* ql, int* qc, int z, int** b, int l, int c)
{
    printf("replaceMatrixinCollection [%d] (%dx%d) --> (%dx%d)\n", z, ql[z], qc[z], l, c);
	int ***a;
	int i, j, k;
	int qlk, qck;

	a = malloc(nw * sizeof(int**));
	for (k = 0; k < nw; k++) {
		if (k == z) { qlk = l; } else { qlk = ql[k]; }
		a[k]=malloc(qlk * sizeof(int*));
		for (i = 0; i < qlk; i++) {
			if (k == z) { qck = c; } else { qck = qc[k]; }
			a[k][i] = malloc(qck * sizeof(int));
			for (j = 0; j < qck; j++){
				if (k != z) { a[k][i][j] = q[k][i][j];	}
				else { a[k][i][j]=b[i][j]; }
			}
		}
	}
	freeCollection(q,nw,ql,qc);
	ql[z]=l;
	qc[z]=c;
	return a;
}


