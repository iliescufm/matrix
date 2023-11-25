/* Cube.c 
   v1.0   */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Matrix.h"

int addMatrixtoCube(int ***q, int* nk, int* ql, int* qc, int **a, int l, int c)
{
	if (*nk < 0) return 1;
    
    int i,j;

    int nz = *nk + 1; 

    if (nz > 1) {
        // ql = (void *)realloc(ql, nz * sizeof(int));
        // qc = (void *)realloc(qc, nz * sizeof(int));
        // q = (void *)realloc(q, nz * sizeof(int***));
    }
    
    ql[*nk] = l;
    qc[*nk] = c;

    q[*nk] = malloc (l * sizeof(int*));
	for (i = 0; i < l; i++)
		{
            q[*nk][i] = malloc( c * sizeof(int));		
			for (j = 0; j < c; j++){
				q[*nk][i][j] = a[i][j];
			}
		}
    *nk = nz;

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
    int*** q = malloc(1 * sizeof(int**));
    int *ql = malloc(10 * sizeof(int));
    int *qc = malloc(10 * sizeof(int));
    int nk = 0;

    int** a;
    int l,c;

    l = 4;
    c = 3;
    a = initAllocMatrix(l,c,10);
    addMatrixtoCube(q,&nk,ql,qc,a,l,c);
    freeMatrix(a,l);

    q = (void *)realloc(q, 3 * sizeof(int**));


    l = 3;
    c = 7;
    a = initAllocMatrix(l,c,20);
    addMatrixtoCube(q,&nk,ql,qc,a,l,c);
    freeMatrix(a,l);

    l = 5;
    c = 5;
    a = initAllocMatrix(l,c,30);
    addMatrixtoCube(q,&nk,ql,qc,a,l,c);
    freeMatrix(a,l);


    printCube(q,nk,ql,qc);
    freeCube(q,nk,ql,qc);
    free(ql);
    free(qc);
}

