#include <stdio.h>
#include "Matrix.h"
#include "PowerMarix.h"


int main(int argc, char* argv[])
{
    int x = 2;
    int n = 2;

    int size = 2;
    int** matrix = initAllocMatrix(size,size,21);
    powerMatrix(matrix, size, n);

    printMatrix(matrix,size,size);

}