/*
Matrix.c
v1.2



*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* initAllocVector(int z, int v)
{
	int i;
	int* a;

	a = malloc(z * sizeof(int));

	for (i=0;i<z;i++)
		a[i] = v;

	return a;
}

int* resizeVector(int* a, int z, int nz)
{
	printf("resizeVector %d-->%d\n",z,nz);
	int* t;
	int i,x1,x2;
	t = malloc(nz * sizeof(int));

	if (z < nz) {x1 = z; x2 = nz;} else {x1 = nz; x2 = 0;}

	for (i = 0; i < x1; i++) t[i] = a[i];
	for (i = x1; i < x2; i++) t[i] = -1;
	free(a);
	return t;
}

void printVector(int *a, int n)
{
	printf("printVector %d\n",n);
	int i;
	for (i=0; i<n; i++)
	{
		printf("%2d ",a[i]);
	}
	printf("\n");
}

void printMatrix(int **a, int nl, int nc)
{
    printf("printMatrix %dx%d\n",nl,nc);
	int i,j;
	for (i=0; i<nl; i++)
	{
		for (j=0; j<nc; j++){
			printf("%3d ",a[i][j]);
		}
		printf("\n");

	}
}

void freeMatrix(int **a, int nl)
{
    printf("freeMatrix %d\n",nl);
	for (int i=0; i<nl; i++)
	{
		free(a[i]);
	}
	free(a);
}

int** cutMatrix(int** b, int* l, int* c, int nl, int *li, int nc, int *ci)
{
	printf("cutMatrix %dx%d --> %dx%d\n", *l, *c, nl, nc);
	int **a;
	int i,j;
	
	a = malloc(nl * sizeof(int*));
	for (i = 0; i < nl; i++) {
		a[i] = malloc(nc * sizeof(int));
		for (j = 0; j < nc; j++){
			a[i][j] = b[li[i]][ci[j]];
		}
	}
	freeMatrix(b, *l);
	*l = nl;
	*c = nc;
	return a;
}

int** transposeMatrix(int** b, int* l, int* c)
{
	printf("transposeMatrix %dx%d --> %dx%d\n",*l,*c,*c,*l);
	int **a;
	int i,j;
	int nl = *c;
	int nc = *l;
	
	a = malloc(nl * sizeof(int*));
	for (i = 0; i < nl; i++) {
		a[i] = malloc(nc * sizeof(int));
		for (j = 0; j < nc; j++){
			a[i][j] = b[j][i];
		}
	}
	freeMatrix(b, *l);
	*l = nl;
	*c = nc;
	return a;
}

int** reizeMatrix(int** b, int nl, int nc, int zl, int zc)
{
	printf("reizeMatrix %dx%d --> %dx%d\n",nl,nc,zl,zc);
	int **a;
	int i,j;
	
	a = malloc(zl * sizeof(int*));

	int x1,x2;

	if (nl < zl) {x1 = nl; x2 = zl;} else {x1 = zl; x2 = 0;}

	for (i=0; i<x1; i++) {
		a[i] = resizeVector(b[i],nc,zc);
		}
	
	for (i=x1; i<x2; i++) {
		a[i] = initAllocVector (zc, -1);
	}

	return a;
}


void printMatrixbyIndex(int **a, int k, int *ql, int *qc)
{
    int nl=ql[k];
    int nc=qc[k];

    printf("printMatrixbyIndex %dx%d\n",nl,nc);
	int i,j;
	for (i=0; i<nl; i++)
	{
		for (j=0; j<nc; j++){
			printf("%3d ",a[i][j]);
		}
		printf("\n");

	}
}


void addMatrixtoCube(int ***c, int **a, int k, int nl, int nc)
{
	int i,j;
		for (i = 0; i < nl; i++)
		{
			for (j = 0; j < nc; j++){
				c[k][i][j] = a[i][j];
			}
		}
}


int** initAllocMatrix(int nl, int nc, int v)
{
	int **a;
	int i,j;

	a = malloc(nl * sizeof(int*));
	for (i = 0; i < nl; i++) {
		a[i] = malloc(nc * sizeof(int));
	}

	for (i = 0; i < nl; i++)
	{
		for (j = 0; j < nc; j++){
			a[i][j] = v;
		}
	}
	return a;
}

int **stringToMatrix(char *mx, int *rows, int *columns) {
    // Count the number of rows
    *rows = 1;
    for (int i = 0; mx[i] != '\0'; i++) {
        if (mx[i] == ',') {
            (*rows)++;
        }
    }

    // Count the number of columns in the first row
    *columns = 1;
    for (int i = 0; mx[i] != '\0' && mx[i] != ','; i++) {
        if (mx[i] == ' ') {
            (*columns)++;
        }
    }

    // Allocate memory for the matrix
    int **matrix = (int **)malloc((*rows) * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
        matrix[i] = (int *)malloc((*columns) * sizeof(int));
    }

    // Populate the matrix
    char *token = strtok(mx, " ,");
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *columns; j++) {
            if (token == NULL) {
                fprintf(stderr, "Error: Not enough elements in the matrix.\n");
                exit(EXIT_FAILURE);
            }
            matrix[i][j] = atoi(token);
            token = strtok(NULL, " ,");
        }
    }

    return matrix;
}
