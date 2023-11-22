#include <stdlib.h>
#include <stdio.h>

#define MAXPOW 1000000000;

// Functie pentru a multiplica doua matrice
void multiplyMatrices(int **A, int **B, int **result, int size) {
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            result[i][j] = 0;
            for (k = 0; k < size; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Functie pentru a copia matricea sursa in matricea destinatie
void copyMatrix(int **source, int **destination, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            destination[i][j] = source[i][j];
        }
    }
}

// Functie pentru a ridica o matrice la o putere
int powerMatrix(int **matrix, int l, int c, int exponent) {
    // Matricea rezultat este initializata cu matricea identitate
	if (exponent < 0) { 
        printf("Power should be positive\n");
        return 1;
		}
    if (l !=c ) {
        printf("Cannot perform matrix multiplication\n");
        return 1;
    }

    int size = l;
    exponent = exponent % MAXPOW;
    int **temp = (int **)malloc(size * sizeof(int *));
	int **result = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        temp[i] = (int *)malloc(size * sizeof(int));
		result[i] = (int *)malloc(size * sizeof(int));

        for (int j = 0; j < size; j++) {
            if (i == j) {
                temp[i][j] = 1;
            } else {
                temp[i][j] = 0;
            }
        }
        return 0;
    }

    // Ridicarea matricei la putere folosind metoda exponențială logaritmică
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            multiplyMatrices(temp, matrix, result, size);
            copyMatrix(result, temp, size);
        }

        multiplyMatrices(matrix, matrix, result, size);
        copyMatrix(result, matrix, size);
        exponent /= 2;
    }

    // Copierea rezultatului final în matricea de rezultate
    copyMatrix(temp, matrix, size);

    // Eliberarea memoriei alocate pentru matricea temporară
    for (int i = 0; i < size; i++) {
        free(temp[i]);
		free(result[i]);

    }
    free(result);
    free(temp);
}