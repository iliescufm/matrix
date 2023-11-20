/*
matlab.c
v1.1

gcc matlab.c stringToMatrix.c Matrix.c Collection.c

*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Collection.h"

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

	int z=0;   //collection size;
    b = initAllocMatrix(5,3,18);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 5, 3);
	freeMatrix(b,ql[z]);

	b = initAllocMatrix(2,3,9);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 2, 3);
	freeMatrix(b,ql[z]);

    q = resizeCollectionCapacity(q,nz,nz*2,ql,qc);
	nz = nz * 2;

	b = initAllocMatrix(5,5,20);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 5, 5);
	freeMatrix(b,ql[z]);

    printCollection(q,z,ql,qc);


	b = initAllocMatrix(3,7,10);
	q = replaceMatrixinCollection(q, z, ql, qc, 0, b, 3, 7);
	q = replaceMatrixinCollection(q, z, ql, qc, 1, b, 3, 7);
	q = replaceMatrixinCollection(q, z, ql, qc, 2, b, 3, 7);
	freeMatrix(b,ql[z]);

	b = initAllocMatrix(2,5,21);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 2, 5);
	freeMatrix(b,ql[z]);

    printCollection(q,z,ql,qc);
	freeCollection(q,z,ql,qc);

return 0;
}

