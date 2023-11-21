/*
Exponent.c
v1.0

Exponentiation by squaring
Montgomery's ladder technique

https://en.wikipedia.org/wiki/Exponentiation_by_squaring

*/


#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"



void int_to_bin_digit(unsigned int in, int count, int* out)
{
    /* assert: count <= sizeof(int)*CHAR_BIT */
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}

int countBinaryDigits(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n > 0) {
        n = n / 2;
        count++;
    }
    return count;
}

int exponentiation(int x, int n)
{
//Montgomery's ladder technique
    int k = countBinaryDigits(n);
    int* nb; // binary expansion of a positive, non-zero integer n
    nb = malloc (k * sizeof(int));
    int_to_bin_digit(n, k, nb);
    // printVector(nb,k);
    int x1 = x;
    int x2 = x*x;
    for (int i = 1; i < k; i++)
    {
        // printf("nb[%d] = %d ",i,nb[i]);
        if (nb[i] == 0) {
            x2 = x1 * x2;
            x1 = x1 * x1;
        }
        else {
            x1 = x1 * x2;
            x2 = x2 * x2;
        }
    }
    // printf("\n");
    return x1;
    
}