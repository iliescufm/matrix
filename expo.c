#include <stdio.h>
#include "Matrix.h"


int main(int argc, char* argv[])
{
    int x = 2;
    int n = 2;

    int size = 4;
    int** matrix = initAllocMatrix(size,size,1);
    int** result = initAllocMatrix(size,size,-1);
    powerMatrix(matrix, result, size, n);

    printMatrix(result,size,size);

}