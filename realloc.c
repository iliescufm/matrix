#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initial size of the vector
    int initialSize = 5;

    // Allocate memory for the vector
    int *vector = (int *)malloc(initialSize * sizeof(int));
    if (vector == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Populate the vector with some values
    for (int i = 0; i < initialSize; i++) {
        vector[i] = i * 2;
    }

    // Print the original vector
    printf("Original Vector:\n");
    for (int i = 0; i < initialSize; i++) {
        printf("%d [%X] ", vector[i], vector+i);
    }
    printf("\n");

    // Resize the vector using realloc
    int newSize = 10;
    int *resizedVector = (int *)realloc(vector, newSize * sizeof(int));

    if (resizedVector == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        free(vector);  // Release the original memory
        return 1;
    }

    // If realloc was successful, use the resizedVector pointer 
    vector = resizedVector;

    // Populate the additional elements in the resized vector
    for (int i = initialSize; i < newSize; i++) {
        vector[i] = i * 2;
    }

    // Print the resized vector
    printf("Resized Vector:\n");
    for (int i = 0; i < newSize; i++) {
        printf("%d [%x] ", vector[i], &vector[i]);
        
    }
    printf("\n");

    // Free the memory when you're done using it
    free(vector);

    return 0;
}
