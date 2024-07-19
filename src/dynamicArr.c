#include <stdio.h>
#include <stdlib.h>

/*
 * The purpose of this file is to create a dynamically re-sizeable array in C
 * since I will never know how many keyboards someone might have, I need a dynamic array
 */

// d_Arr = Dynamic Array
typedef struct {
    int *data;
    int size;
    int capacity;
} d_Arr;

// Initialize the dynamic array
void init_array(d_Arr *arr) {
    arr->size = 0;
    // Initial capacity is two because I assume most people have a laptop keyboard, and normal keyboard
    // This will increase if needed, but remember a realloc is needed every time you increase the size
    arr->capacity = 2;
    arr->data = malloc(arr->capacity * sizeof(int));
    if (arr->data == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}

// Append an element to the dynamic array
void append(d_Arr *arr, int value) {
    // Check if we need to resize the array
    if (arr->size >= arr->capacity) {
	// Doubling ensures that the amortized cost of append operations remains constant time, O(1).
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(int));
        if (arr->data == NULL) {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
    }
    arr->data[arr->size++] = value;
}
/*

int main() {
	d_Arr arr;
	init_array(&arr);

	// Append elements to the array
	for (int i = 0; i < 10; i++) {
		append(&arr, i + 1);
	}
// return arr.data; 
	// Print the elements in the array
	printf("Array elements: ");
	for (int i = 0; i < arr.size; i++) {
		printf("%d ", arr.data[i]);
	}
	printf("\n");

	// Free the allocated memory
	free(arr->data);

	return 0;
}
*/
