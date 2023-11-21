#include <stdio.h>
#include "Exponent.h"


int main(int argc, char* argv[])
{
    int x = 2;
    int n = 8;
    int xn = exponentiation(x,n);
    printf("%d^%d = %d\n",x,n,xn);
    return 0;
}