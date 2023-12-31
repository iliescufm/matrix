#include <stdio.h>
#include <stdlib.h>

#define D 1

// Functie pentru a aduna doua matrice
void addMatrices(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Functie pentru a scadea doua matrice
void subtractMatrices(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Functie pentru a inmulti doua matrice folosind algoritmul lui Strassen
void strassenMultiply(int **A, int **B, int **C, int size) {
    if (size == 1) {
        // Cazul de baza: inmultirea a doua matrice 1x1
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    // Impartirea matricelor in patru submatrici
    int newSize = size / 2;

    int **A11, **A12, **A21, **A22;
    int **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    int **M1, **M2, **M3, **M4, **M5, **M6, **M7;

    // Alocare de memorie pentru submatrici
    A11 = (int **)malloc(newSize * sizeof(int *));
    A12 = (int **)malloc(newSize * sizeof(int *));
    A21 = (int **)malloc(newSize * sizeof(int *));
    A22 = (int **)malloc(newSize * sizeof(int *));
    B11 = (int **)malloc(newSize * sizeof(int *));
    B12 = (int **)malloc(newSize * sizeof(int *));
    B21 = (int **)malloc(newSize * sizeof(int *));
    B22 = (int **)malloc(newSize * sizeof(int *));
    C11 = (int **)malloc(newSize * sizeof(int *));
    C12 = (int **)malloc(newSize * sizeof(int *));
    C21 = (int **)malloc(newSize * sizeof(int *));
    C22 = (int **)malloc(newSize * sizeof(int *));
    M1 = (int **)malloc(newSize * sizeof(int *));
    M2 = (int **)malloc(newSize * sizeof(int *));
    M3 = (int **)malloc(newSize * sizeof(int *));
    M4 = (int **)malloc(newSize * sizeof(int *));
    M5 = (int **)malloc(newSize * sizeof(int *));
    M6 = (int **)malloc(newSize * sizeof(int *));
    M7 = (int **)malloc(newSize * sizeof(int *));

    for (int i = 0; i < newSize; i++) {
        A11[i] = (int *)malloc(newSize * sizeof(int));
        A12[i] = (int *)malloc(newSize * sizeof(int));
        A21[i] = (int *)malloc(newSize * sizeof(int));
        A22[i] = (int *)malloc(newSize * sizeof(int));
        B11[i] = (int *)malloc(newSize * sizeof(int));
        B12[i] = (int *)malloc(newSize * sizeof(int));
        B21[i] = (int *)malloc(newSize * sizeof(int));
        B22[i] = (int *)malloc(newSize * sizeof(int));
        C11[i] = (int *)malloc(newSize * sizeof(int));
        C12[i] = (int *)malloc(newSize * sizeof(int));
        C21[i] = (int *)malloc(newSize * sizeof(int));
        C22[i] = (int *)malloc(newSize * sizeof(int));
        M1[i] = (int *)malloc(newSize * sizeof(int));
        M2[i] = (int *)malloc(newSize * sizeof(int));
        M3[i] = (int *)malloc(newSize * sizeof(int));
        M4[i] = (int *)malloc(newSize * sizeof(int));
        M5[i] = (int *)malloc(newSize * sizeof(int));
        M6[i] = (int *)malloc(newSize * sizeof(int));
        M7[i] = (int *)malloc(newSize * sizeof(int));
    }

    // Initializarea submatricilor
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculul valorilor M1 pana la M7


    addMatrices(A11, A22, C11, newSize); // not true C11, use it temporary for add
    addMatrices(B11, B22, C12, newSize); // not true C12, use it temporary for add
    strassenMultiply(C11, C12, M1, newSize); // M1 = (A11 + A22) * (B11 + B22)
    addMatrices(A21, A22, C11, newSize); 
    strassenMultiply(C11, B11, M2, newSize); // M2 = (A21 + A22) * B11
    subtractMatrices(B12, B22, C11, newSize);
    strassenMultiply(A11, C11, M3, newSize); // M2 = A11 * (B12 - B22)
    subtractMatrices(B21, B11, C11, newSize);
    strassenMultiply(A22, C11, M4, newSize); // M4 = A22 * (B21 - B11)
    addMatrices(A11, A12, C11, newSize);
    strassenMultiply(C11, B22, M5, newSize); // M5 = (A11 + A12) * B22
    subtractMatrices(A21, A11, C11, newSize);
    addMatrices(B11, B12, C12, newSize);
    strassenMultiply(C11, C12, M6, newSize); // M6 = (A21 - A11) * (B11 + B12)
    subtractMatrices(A12, A22, C11, newSize);
    addMatrices(B21, B22, C12, newSize);
    strassenMultiply(C11, C12, M7, newSize);

    // Calculul submatricilor rezultat
    addMatrices(M1, M4, A11, newSize);
    subtractMatrices(A11, M5, A12, newSize);
    addMatrices(A12, M7, C11, newSize); // C11 = M1 + M4 - M5 + M7
    addMatrices(M3, M5, C12, newSize);  // C12 = M3 + M5
    addMatrices(M2, M4, C21, newSize);  // C21 = M2 + M4
    addMatrices(M1, M3, A11, newSize);
    subtractMatrices(A11, M2, A12, newSize);
    addMatrices(A12, M6, C22, newSize); // C22 = M1 + M3 - M2 + M6

    // Copierea rezultatului in matricea de rezultate
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Eliberarea memoriei alocate pentru submatrici
    for (int i = 0; i < newSize; i++) {
        free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]);
        free(B11[i]); free(B12[i]); free(B21[i]); free(B22[i]);
        free(C11[i]); free(C12[i]); free(C21[i]); free(C22[i]);
        free(M1[i]); free(M2[i]); free(M3[i]); free(M4[i]);
        free(M5[i]); free(M6[i]); free(M7[i]);
    }
    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(C11); free(C12); free(C21); free(C22);
    free(M1); free(M2); free(M3); free(M4);
    free(M5); free(M6); free(M7);
}
