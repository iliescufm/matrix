/*
strassen.c
v1.0

Exemple: strassenMultiply

gcc strassen.c Strassen.c Matrix.c
https://www.geeksforgeeks.org/strassens-matrix-multiplication/
*/

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "Strassen.h"

int main() {
    char strA[] = "-4 1 5 -2, -1 2 1 2, 3 0 5 -1, 2 1 1 4";
    char strB[] = "2 -2 -4 -1, 0 2 0 3, 1 3 -3 -2, 1 -4 -5 -2";

    int la,ca;
    int** a = stringToMatrix(strA,&la,&ca);

    int lb,cb;
    int** b = stringToMatrix(strB,&lb,&cb);

    int l = la;

    int **c = initAllocMatrix(l,l,0);
   
    strassenMultiply(a, b, c, l);

    printMatrix(c, l, l);

    freeMatrix(a,l);
    freeMatrix(b,l);
    freeMatrix(c,l);

    return 0;
}
