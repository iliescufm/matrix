/*
sortvector.c
v 1.0

gcc sortvector.c Radix.c

*/

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

    printf("Example 1\n");

	int arr[] = { 543, 986, 217, 765, 329, 12, 114, 999, 5 };
  	int vct[] = { 543, 986, 217, 765, 329, 12, 114, 999, 5 };

    int *idx;
	int n = sizeof(arr) / sizeof(arr[0]);

    printf("Example 2\n");
   	print(arr, n);   
    idx = sortVector(arr,n);
	print(arr, n);
    print(idx, n);
    printf(" - use top index\n");
    for (int i = 0; i < n;  i++){
        printf(" %3d",vct[idx[i]]);
    }
    printf("\n");

    printf("Example 2\n");
    int* v = malloc(3 * sizeof(int));
    v[0] = 18;
    v[1] = 21;
    v[2] = 10;
    idx = sortVector(v,3);
	print(v, 3);
    print(idx, 3);

	return 0;
}
