#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Exponent.h"

# define D 1

// printCollection (collection, size, linesvector, columnsvector)
void printCollection(int ***a, int z, int *l, int *c)
{
    if (D) printf("printCollection /%d/\n", z);
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

void printCollectionandSum(int ***a, int z, int *l, int *c, int *sum)
{
    if (D) printf("printCollectionandSum /%d/\n", z);
	int i,j,k;
	for(k = 0; k < z; k++) {
		sum[k] = sumMatrix(a[k], l[k], c[k]);
		printf("#%d $%d\n", k, sum[k]);
		printMatrix(a[k], l[k], c[k]);
	}
}

// freeCollection(collection, size, linesvector, columnsvector)
void freeCollection(int ***a, int z, int *l, int *c)
{
    if (D) printf("freeCollection /%d/\n", z);
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
    if (D) printf("addMatrixtoCollection [%d] [%d x %d]\n", *z, l, c);
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

int*** sortCollection(int ***q, int z, int *ql, int *qc, int *top)
{
    if (D) printf("sortCollection #%d \n", z);
	int ***a;
	int i,j,k;
	int *ol = malloc(z * sizeof(int));
	int *oc = malloc(z * sizeof(int));
	for (k=0 ; k < z ; k++) {
		ol[k] = ql[k];
		oc[k] = qc[k];
	}

	a = malloc(z * sizeof(int**));
	for (k = 0; k < z; k++) {
		a[k]=malloc(ql[top[k]] * sizeof(int*));
		for (i = 0; i < ql[top[k]]; i++) {
			a[k][i] = malloc(qc[top[k]] * sizeof(int));
				for (j = 0; j < qc[top[k]]; j++){
						a[k][i][j] = q[top[k]][i][j];
				}
		}
	}
	freeCollection(q,z,ql,qc);
	for (k=0 ; k < z ; k++) {
		ql[k] = ol[top[k]]; 
		qc[k] = oc[top[k]]; 
	}
	free(ol);
	free(oc);
	return a;
}

// resize = resizeCollectionCapacity(collection, size, newsize, linesvector, columnsvector)
int*** resizeCollectionCapacity(int ***w, int z, int nz, int *l, int *c) 
{
    if (D) printf("resizeCollection %d-->%d\n",z,nz);
    
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
    if (D) printf("replaceMatrixinCollection [%d] (%dx%d) --> (%dx%d)\n", z, ql[z], qc[z], l, c);
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

int*** deleteMatrixfromCollection(int*** q, int* nw, int* ql, int* qc, int z)
{
    if (D) printf("deleteMatrixfromCollection #%d %d\n", *nw, z);
	int ***a;
	int i, j, k, ka =0;

	int* qlo = echoVector(ql,*nw);
	int* qco = echoVector(qc,*nw);
	int* qlk = realloc(ql, (*nw - 1) * sizeof(int));
	int* qck = realloc(qc, (*nw - 1) * sizeof(int));

	a = malloc((*nw -1) * sizeof(int**));
	for (k = 0; k < *nw; k++) {
		if (k != z) { 
			qlk[ka] = ql[k];
			qck[ka] = qc[k];
		    a[ka]=malloc(ql[k] * sizeof(int*));
			for (i = 0; i < ql[k]; i++) {
				a[ka][i] = malloc(qc[k] * sizeof(int));
				for (j = 0; j < qc[k]; j++)
						a[ka][i][j] = q[k][i][j];
				}
		ka++;
		}
	}
	printf("ql,qc\n");
	printVector(qlo,*nw);
	printVector(qco,*nw);

	//freeCollection(q,*nw,ql,qc);
	*nw = *nw - 1;
	return a;
}

