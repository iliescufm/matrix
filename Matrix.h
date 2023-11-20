int* initAllocVector(int z, int v);
// vector = initAllocVector(size, value)

int* resizeVector(int*, int, int);
// resized = resizeVector(vector, size, newsize)

void printVector(int *, int);
// printVector(vector, size) 

void printMatrix(int **, int, int);
// printMatrix(matrix, lines, columns)

int** transposeMatrix(int**, int*, int*);
// transpose = transposeMatrix(matrix, lines-pointer, columns-pointer)

int** reizeMatrix(int** , int, int, int, int);
// resized = reizeMatrix(matrix, lines, columns, newlines, newcolumns)

void freeMatrix(int **, int);
// freeMatrix(matrix, lines)

int** initAllocMatrix(int , int, int);
// matrix = initAllocMatrix (lines, columns, value)


// matrix = stringToMatrix(string, rows-pointer, columns-pointer)
int **stringToMatrix(char *mx, int *rows, int *columns);
