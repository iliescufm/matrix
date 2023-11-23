int* initAllocVector(int z, int v);
// vector = initAllocVector(size, value)

int* resizeVector(int*, int, int);
// resized = resizeVector(vector, size, newsize)

int* reallocVector(int* a, int nz);

void printVector(int *, int);
// printVector(vector, size) 

void printVectorAddr(int *a, int n);
void infoVector(char* m, int *a, int n, int addr);


int* echoVector(int*, int);
//vector = echoVector(vector, size)

int sumMatrix(int **a, int nl, int nc);
// sum = sumMatrix (matrix, lines, colums);

void printMatrix(int **, int, int);
// printMatrix(matrix, lines, columns)

void printMatrixAddr(int **, int, int);
// printMatrix(matrix, lines, columns)

int** transposeMatrix(int**, int*, int*);
// transpose = transposeMatrix(matrix, lines-pointer, columns-pointer)

// matrix = (matrix, lines-p, columns-p, n-lines-to-cut, lines-to-cut, n-col-to-cut, cols-to-cut)
int** cutMatrix(int**, int*, int*, int, int*, int, int*);

int** reizeMatrix(int** , int, int, int, int);
// resized = reizeMatrix(matrix, lines, columns, newlines, newcolumns)

void freeMatrix(int **, int);
// freeMatrix(matrix, lines)

int** initAllocMatrix(int , int, int);
// matrix = initAllocMatrix (lines, columns, value)


// matrix = stringToMatrix(string, rows-pointer, columns-pointer)
int **stringToMatrix(char *mx, int *rows, int *columns);

int* stringToVector(char *mx, int *columns);

int** readMatrixforKeyboard(int nl, int nc);
