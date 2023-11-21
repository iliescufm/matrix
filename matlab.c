/*
matlab.c
v1.3

gcc matlab.c Radix.c Matrix.c Collection.c

*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Collection.h"
#include "Radix.h"


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
    b = initAllocMatrix(5,3,1);
	sum[z] = sumMatrix(b,5,3);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 5, 3);
	freeMatrix(b,ql[z]);

	b = initAllocMatrix(2,3,2);
	sum[z] = sumMatrix(b,2,3);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 2, 3);
	freeMatrix(b,ql[z]);

    q = resizeCollectionCapacity(q,nz,nz*2,ql,qc);
	nz = nz * 2;

	b = initAllocMatrix(5,5,0);

	sum[z] = sumMatrix(b,5,5);
	q = addMatrixtoCollection(q, &z, ql, qc, b, 5, 5);
	freeMatrix(b,ql[z]);

    printCollectionandSum(q,z,ql,qc,sum);

	top = sortVector(sum,z);
	printVector(top,z);

	for (k = 0; k < z; k++) {
		printf("a[%d]=malloc(%d * sizeof(int*))\n",k,ql[top[k]]);
		for (i = 0; i < ql[top[k]]; i++) {
			printf("a[%d][%d] = malloc(%d * sizeof(int))\n",k,i,qc[top[k]]);
				for (j = 0; j < qc[top[k]]; j++){
						printf("a[%d][%d][%d] = %d\n",k,i,j,q[top[k]][i][j]);
				}
		}
	}

	q = sortCollection(q,z,ql,qc,top);
    printCollectionandSum(q,z,ql,qc,sum);


	
	// b = initAllocMatrix(3,7,10);
	// q = replaceMatrixinCollection(q, z, ql, qc, 0, b, 3, 7);
	// q = replaceMatrixinCollection(q, z, ql, qc, 1, b, 3, 7);
	// q = replaceMatrixinCollection(q, z, ql, qc, 2, b, 3, 7);
	// freeMatrix(b,ql[z]);

	// int bl;
	// int bc;
	// char m1[] = "1 0 1 1,1 1 1 1, 1 0 2 2";
	// b = stringToMatrix(m1, &bl, &bc);
	// printMatrix(b,bl,bc);
	// q = addMatrixtoCollection(q, &z, ql, qc, b, bl, bc);
	// int li[] = {0,1};
	// int lc[] = {0,2,3};
	// b = cutMatrix(b,&bl,&bc,2,li,3,lc);
	// q = replaceMatrixinCollection(q, z, ql, qc, 1, b, bl, bc);
	// int s = sumMatrix(b,bl,bc);

	// freeMatrix(b,bl);

    // printCollection(q,z,ql,qc);
	//freeCollection(q,z,ql,qc);

return 0;
}

