#include <stdio.h>
#include "Radix.h"
#include <stdlib.h>

// A utility function to print an array
void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		printf(" %3d",arr[i]);
    printf("\n");
}


int main()
{
	int arr[] = { 543, 986, 217, 765, 329, 12, 114, 999, 5 };
    int *idx;
	int n = sizeof(arr) / sizeof(arr[0]);

   	print(arr, n);   
    idx = sortVector(arr,n);
	print(arr, n);
    print(idx, n);

    n=3;
    int* v = malloc(n * sizeof(int));
    v[0] = 18;
    v[1] = 21;
    v[2] = 10;
    idx = sortVector(v,n);
	print(v, n);
    print(idx, n);

	return 0;
}
