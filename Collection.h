// printCollection(collection, size, linesvector, columnsvector)
void printCollection(int ***, int, int*, int*);

// freeCollection(collection, size, linesvector, columnsvector)
void freeCollection(int ***, int, int*, int*);

// addMatrixtoCollection(collection, size, linesvector, columnsvector, matrix, lines, columns)
int*** addMatrixtoCollection(int***, int*, int*, int*, int**, int, int);

int addMatrixtoCube(int ***q, int* qz, int* ql, int* qc, int **a, int l, int c);


// collection = resizeCollectionCapacity(collection, size, newsize, linesvector, columnsvector)
int*** resizeCollectionCapacity(int***, int, int, int*, int*); 

int*** appendMatrixtoCollection(int*** q, int* size, int* capa, int* ql, int* qc, int** b, int l, int c);

// collection = replaceMatrixinCollection(colection, size, linesvector, columnsvector, index, matrix, lines, columns)
int*** replaceMatrixinCollection(int***, int, int*, int*, int, int**, int, int);

void printCollectionandSum(int ***a, int z, int *l, int *c, int *sum);

int sortCollection(int ***q, int z, int *ql, int *qc, int *top);

int*** sortCube(int ***q, int z, int *ql, int *qc, int *top);


//collection = deleteMatrixfromCollection(collection, size-pointer, lines-vector, columns-vector, index-delete)
int*** deleteMatrixfromCollection(int*** q, int* z, int* ql, int* qc, int ki);

int deleteMatrixfromCube(int*** q, int* z, int* ql, int* qc, int ki);

