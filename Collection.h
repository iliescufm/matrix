// printCollection(collection, size, linesvector, columnsvector)
void printCollection(int ***, int, int*, int*);

// freeCollection(collection, size, linesvector, columnsvector)
void freeCollection(int ***, int, int*, int*);

// addMatrixtoCollection(collection, size, linesvector, columnsvector, matrix, lines, columns)
int*** addMatrixtoCollection(int***, int*, int*, int*, int**, int, int);

// collection = resizeCollectionCapacity(collection, size, newsize, linesvector, columnsvector)
int*** resizeCollectionCapacity(int***, int, int, int*, int*); 

// collection = replaceMatrixinCollection(colection, size, linesvector, columnsvector, index, matrix, lines, columns)
int*** replaceMatrixinCollection(int***, int, int*, int*, int, int**, int, int);

void printCollectionandSum(int ***a, int z, int *l, int *c, int *sum);

int*** sortCollection(int ***q, int z, int *ql, int *qc, int *top);

void exponentMatrixinCollection(int ***q,int z,int* ql, int* qc,int k,int n);

