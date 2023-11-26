// C++ implementation of Radix Sort
// https://www.geeksforgeeks.org/radix-sort/

// A utility function to get maximum
// value in arr[]
# include <stdlib.h>
int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

// A function to do counting sort of arr[]
// according to the digit
// represented by exp.
void countSort(int arr[], int n, int exp)
{

	// Output array
	int output[n];
	int i, count[10] = { 0 };

	// Store count of occurrences
	// in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i]
	// now contains actual position
	// of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Copy the output array to arr[],
	// so that arr[] now contains sorted
	// numbers according to current digit
	for (i = 0; i < n; i++)
		arr[i] = output[i];
}

// void countSortIdx(int arr[], int idx[], int n, int exp)
// {

// 	// Output array
// 	int output[n];
// 	int i, count[10] = { 0 };

// 	// Store count of occurrences
// 	// in count[]
// 	for (i = 0; i < n; i++)
// 		count[(arr[i] / exp) % 10]++;

// 	// Change count[i] so that count[i]
// 	// now contains actual position
// 	// of this digit in output[]
// 	for (i = 1; i < 10; i++)
// 		count[i] += count[i - 1];

// 	// Build the output array
// 	for (i = n - 1; i >= 0; i--) {
// 		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
// 		count[(arr[i] / exp) % 10]--;
// 	}

// 	// Copy the output array to arr[],
// 	// so that arr[] now contains sorted
// 	// numbers according to current digit
// 	for (i = 0; i < n; i++)
// 		arr[i] = output[i];
// }

// The main function to that sorts arr[]
// of size n using Radix Sort
void radixsort(int arr[], int n)
{

	// Find the maximum number to
	// know number of digits
	int m = getMax(arr, n);

	// Do counting sort for every digit.
	// Note that instead of passing digit
	// number, exp is passed. exp is 10^i
	// where i is current digit number
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

int findElementinVector(int odx[],int n, int e){
	int i;
	int f = -1;
	for (i=0; i < n; i++)
        if (odx[i] == e) { f = i;break; }
	
	return f;
}

void sortVector(int* arr,int n, int* top){
	int* odx = malloc (n* sizeof(int));
	int i;
	for (i = 0; i < n; i++) 
		odx[i] = arr[i];
	radixsort(arr,n);
	for (i = 0; i < n; i++)
	    top[i] = findElementinVector(odx,n,arr[i]);

	free(odx);
}
