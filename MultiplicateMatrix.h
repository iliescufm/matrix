
// getRow(matrix, index, nr columns)
int* getRow(int**, int, int);

// getColumn(matrix, index, nr lines)
int* getColumn(int**, int, int);

// multiplicateMatrix(matrix1, nr rows, nr cols, matrix2, nr rows, nr cols, matrix-result)
int multiplicateMatrix(int** , int, int, int**, int, int, int**);

// matrix-result = newMatrixMultiplicate(matrix1, nr rows, nr cols, matrix2, nr rows, nr cols)
int** newMatrixMultiplicate(int** m, int x1, int y1, int** n, int x2, int y2);

