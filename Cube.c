/* Cube.c 
   v1.1
   
   gcc Cube.c Collection.c Matrix.c Radix.c PowerMatrix.c -g -O0 -o cube
   valgrind --leak-check=yes ./cube
   
   */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Collection.h"
#include "Radix.h"
#include "PowerMatrix.h"

int addMatrixtoCube(int ***q, int* qz, int* ql, int* qc, int **a, int l, int c)
{
	if (*qz < 0) return 1;
    
    int i,j;

    int nz = *qz + 1; 

    if (nz > 1) {
        // ql = (void *)realloc(ql, nz * sizeof(int));
        // qc = (void *)realloc(qc, nz * sizeof(int));

        // q = (void *)realloc(q, nz * sizeof(int**));

    }
    
    ql[*qz] = l;
    qc[*qz] = c;

    q[*qz] = malloc (l * sizeof(int*));
	for (i = 0; i < l; i++)
		{
            q[*qz][i] = malloc( c * sizeof(int));		
			for (j = 0; j < c; j++){
				q[*qz][i][j] = a[i][j];
			}
		}
    *qz = nz;

    return 0;

}

void printCube(int ***q, int nk, int* ql, int* qc)
{
    printf("Cube [%p]\n", (void *)q);

	int k,i,j;

    for(k = 0; k < nk ; k++)
    {
        printf("#%d\n",k);

		for (i = 0; i < ql[k]; i++)
		{
			for (j = 0; j < qc[k]; j++){
				printf("%3d ",q[k][i][j]);
			}
        printf("\n");
		}
    printf("\n");
    }
}

void freeCube(int ***q, int nk, int* ql, int* qc)
{
    printf("freeCube [%p]\n", (void *)q);

	int k,i,j;

    for(k = 0; k < nk ; k++)
    {
		freeMatrix(q[k],ql[k]);
    }
    free(q);
}

int main()
{
    int qk = 1; //capacity of cube
    int*** q = malloc(qk * sizeof(int**));
    int *ql = malloc(qk * sizeof(int));
    int *qc = malloc(qk * sizeof(int));
    int qz = 0; //size of cube

    int** a;
    int l,c;

    for (int u = 0; u < 11; u++) {

        l = 25 + (u % 2);
        c = 2 + (u % 3);
        a = initAllocMatrix(l,c,2*u);
        addMatrixtoCube(q,&qz,ql,qc,a,l,c);
        freeMatrix(a,l);

        q = (void *)realloc(q, (qz+1) * sizeof(int**));
        ql = realloc(ql, (qz+1) * sizeof(int));
        qc = realloc(qc, (qz+1) * sizeof(int));


    }


    for (int u = 0; u < 11; u++) {
        q[u] = transposeMatrix(q[u],&ql[u],&qc[u]);
    }


    //Sort
    int* sum = malloc(qz * sizeof(int));
    int* top = (int *)calloc(qz,sizeof(int));


    for(int i = 0; i < qz; i++) { 
        sum[i] = sumMatrix(q[i], ql[i], qc[i]); 
        }
		sortVector(sum, qz, top);
	    q = sortCollection(q, qz, ql, qc, top);


    int li[] = {0,1,2,3};
    int ci[] = {2,3,4,5};
    
    q[10] = cutMatrix(q[10],&ql[10],&qc[10],4,li,4,ci);

    powerMatrix(q[10],ql[10],qc[10],2);

    printCube(q,qz,ql,qc);

    freeCube(q,qz,ql,qc);
    free(ql);
    free(qc);
    free(top);
    free(sum);
}

