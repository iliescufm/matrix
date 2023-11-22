/* Matrix.c 
   v1.3    */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

# define D 1
# define MODULO 10007

int* initAllocVector(int z, int v)
{
	int i;
	int* a;

	a = malloc(z * sizeof(int));

	for (i=0;i<z;i++)
		a[i] = v;

	return a;
}

int* echoVector(int* b, int z)
{
	int i;
	int* a;
	a = malloc(z * sizeof(int));

	for (i=0;i<z;i++)
		a[i] = b[i];
	
	return a;

}

int* resizeVector(int* a, int z, int nz)
{
	if (D) printf("resizeVector %d-->%d\n",z,nz);
	int* t;
	t = realloc(a, (nz) * sizeof(int));
	if (t) a = t;
	else printf ("Error-resizeVector 'realloc(a, (nz) * sizeof(int))'\n");

	return a;
}

void printVectorAddr(int *a, int n)
{
	if (D) printf("printVectorAddr %d\n",n);
	int i;
	for (i=0; i<n; i++)
	{
		printf(" %2d [%p]",a[i],(void *)&a[i]);
	}
	printf("\n");
}

void printVector(int *a, int n)
{
	if (D) printf("printVector %d\n",n);
	int i;
	for (i=0; i<n; i++)
	{
		printf(" %2d", a[i]);
	}
	printf("\n");
}

void printMatrix(int **a, int nl, int nc)
{
    if (D) printf("printMatrix %dx%d\n",nl,nc);
	int i,j;
	for (i=0; i<nl; i++)
	{
		for (j=0; j<nc; j++){
			printf("%3d ",a[i][j]);
		}
		printf("\n");

	}
}

void printMatrixAddr(int **a, int nl, int nc)
{
	int i,j;
	for (i=0; i<nl; i++)
	{
		for (j=0; j<nc; j++){
			printf("%3d [%p]",a[i][j],(void *)&a[i][j]);
		}
		printf("\n");

	}
}


int sumMatrix(int **a, int nl, int nc)
{
    if (D) printf("sumMatrix %dx%d = ",nl,nc);
	int i,j;
	int s = 0;
	for (i=0; i<nl; i++)
	{
		for (j=0; j<nc; j++){
			s = s + a[i][j];
		}
	}
	printf("%d\n",s);
	return s % MODULO;
}


void freeMatrix(int **a, int nl)
{
    if (D) printf("freeMatrix %d\n",nl);
	for (int i=0; i<nl; i++)
	{
		free(a[i]);
	}
	free(a);
}

int** cutMatrix(int** b, int* l, int* c, int nl, int *li, int nc, int *ci)
{
	if (D) printf("cutMatrix %dx%d --> %dx%d\n", *l, *c, nl, nc);
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
	if (D) printf("transposeMatrix %dx%d --> %dx%d\n",*l,*c,*c,*l);
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
	if (D) printf("reizeMatrix %dx%d --> %dx%d\n",nl,nc,zl,zc);
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

    if (D) printf("printMatrixbyIndex %dx%d\n",nl,nc);
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

int** readMatrixforKeyboard(int nl, int nc)
{
	if (D) printf("readMatrixforKeyboard %dx%d\n",nl,nc);
	int **a;
	int i,j;

	a = malloc(nl * sizeof(int*));

	for (i = 0; i < nl; i++)
	{
		a[i] = malloc(nc * sizeof(int));
		for (j = 0; j < nc; j++){
			scanf("%d",&a[i][j]);
			a[i][j] = a[i][j] % MODULO;
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

int* stringToVector(char *mx, int *columns) 
{

	int rows;
	int **a = stringToMatrix(mx, &rows, columns);
	return a[0];

}