/*
matlab.c
v1.3

gcc matlab.c Radix.c Exponent.c Matrix.c Collection.c

*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Collection.h"
#include "Radix.h"
#include "Exponent.h"


void pl(){
	printf("-----\n");
}

int main(void)
{
	int nx,ny,nz,i,j,k;
	int **b;
	
	nx = 15;
	ny = 3;

	nz = 2; //collection capacity

	int *ql = malloc(nz * sizeof(int)); //numar de linii ale matricii din colectie
	int *qc = malloc(nz * sizeof(int)); //numar de coloane ale matricii din colectie
    int	***q = malloc(nz * sizeof(int**));
	int *sum = malloc(nz * sizeof(int)); // suma fiecarei matrici din colectie
	int *top = malloc(nz * sizeof(int));// clasament cu pozitia din colectie


	int z=0;   //collection size;
    b = initAllocMatrix(2,2,100);
	sum[z] = sumMatrix(b,2,2);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 2, 2);
	freeMatrix(b,ql[z]);

	b = initAllocMatrix(3,2,20);
	sum[z] = sumMatrix(b,3,2);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 3, 2);
	freeMatrix(b,ql[z]);

    q = resizeCollectionCapacity(q,nz,nz*2,ql,qc);
	nz = nz * 2;

	b = initAllocMatrix(5,5,0);
	sum[z] = sumMatrix(b,5,5);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 5, 5);
	freeMatrix(b,ql[z]);

	b = initAllocMatrix(3,7,2);
	q = replaceMatrixinCollection(q, z, ql, qc, 0, b, 3, 7);
	sum[0] = sumMatrix(b,3,7);
	freeMatrix(b,ql[z]);

	int bl;
	int bc;
	char m1[] = "1 0 1 1,1 1 1 1, 1 0 2 2";
	b = stringToMatrix(m1, &bl, &bc);
	sum[z] = sumMatrix(b, bl, bc);
	q = addMatrixtoCollection(q, &z, ql, qc, b, bl, bc);

	int li[] = {0,1};
	int lc[] = {0,2,3};
	b = cutMatrix(b,&bl,&bc,2,li,3,lc);
	q = replaceMatrixinCollection(q, z, ql, qc, 2, b, bl, bc);
	sum[2] = sumMatrix(b, bl, bc);
	freeMatrix(b,bl);

	exponentMatrixinCollection(q,z,ql,qc,0,4);

    printCollectionandSum(q,z,ql,qc,sum);
	// top = sortVector(sum,z);
	// q = sortCollection(q,z,ql,qc,top);
    // printCollectionandSum(q,z,ql,qc,sum);

	freeCollection(q,z,ql,qc);

return 0;
}

