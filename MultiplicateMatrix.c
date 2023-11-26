//inmultirea a doua matrici
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MODULO 10007

// getRow(matrix, index, nr columns)
int* getRow(int** a, int k, int nc)
{
    int* v = malloc(nc * sizeof(int));
    for(int i = 0; i < nc ; i++) {
        v[i] = a[k][i];
    }
    return v; 
}
// getColumn(matrix, index, nr lines)
int* getColumn(int** a, int k, int nl)
{
    int* v = malloc(nl * sizeof(int));
    for(int i = 0; i < nl ; i++) {
        v[i] = a[i][k];
    }
    return v;     
}

int multiplicateVectors(int* v, int* w, int n)
{
    int s = 0;
    for(int i = 0; i < n; i++) {
        s = s + v[i] * w[i];
    }
    s = s % MODULO;
    if (s < 0) {
        s = s + MODULO;
    }

    return s;
}
//multiplicateMatrix(matrix1, nr rows, nr col, matrix2, nr rows, nr col)
int multiplicateMatrix(int** m, int x1, int y1, int** n, int x2, int y2, int** a)
{
    if(y1 != x2) {
		printf("Cannot perform matrix multiplication\n");
		return 1;
	} else {
        int i,j;

        for (i = 0; i < x1; i++) {
            //
        }
        int* l;
        int* c;
        for (i = 0; i < x1; i++) {
            l = getRow(m, i, y1);
            for (j = 0; j < y2; j++){
                c = getColumn(n, j, x2);
                a[i][j] = multiplicateVectors(l, c, y1);
                free(c);
            }
            free(l);
        }
    }
    return 0;

}

int** newMatrixMultiplicate(int** m, int x1, int y1, int** n, int x2, int y2)
{
    int** a;
    if(y1 != x2) {
		printf("Cannot perform matrix multiplication\n");
		return a;
	} else {
        int i,j;
        a = malloc(x1 * sizeof(int*));
        for (i = 0; i < x1; i++) {
            a[i] = malloc(y2 * sizeof(int));
        }
        int* l;
        int* c;
        for (i = 0; i < x1; i++) {
            l = getRow(m, i, y1);
            for (j = 0; j < y2; j++){
                c = getColumn(n, j, x2);
                a[i][j] = multiplicateVectors(l, c, y1);
                free(c);
            }
            free(l);
        }
    }
    return a;

}