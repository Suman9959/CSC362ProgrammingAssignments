/* Name: Suman Bhandari
 * Date: Nov 14, 2023
 Program #3: Sorting an int array using Bubble Sort and Selection Sort algorithms.
 */
//This program applies the concept of using pointer and pointer arithmetic to change the pointer and
// dereferencing of pointer and passing address of the variable.
// The main function initializes an array, creates a second array, and performs sorting operations.
//Sorting algorithms Bubble Sort and Selection sort are used in this program.
//Bubble Sort algorithm repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order until list is sorted.
//Selection sort algorithm repeatedly selects minimum element from unsorted part and swaps it with first
// unsorted element until everything is sorted.
//The sorting algorithms are implemented using pointer arithmetic to manipulate array elements.
// The program strictly follows  the requirement that all array access must be done using pointers.
// All array manipulations are done through pointers and pointer arithmetic.
// Three primary functions, copy, sort1, and sort2, handle array manipulation, while the output function
// displays the sorted results.





#include <stdio.h>

// Function to copy elements from source to destination array
void copy(int *source, int *destination, int size) {
    int *source_ptr = source;  //Declaring a pointer which points to 1st element of source array
    int *destination_ptr = destination;
    int *i;
// Copying elements from source to the destination array using pointer arithmetic
    for ( i = source_ptr; i < source_ptr + size; i++) {
        *(destination_ptr +(i - source_ptr)) = *i;  // Dereferencing pointers
    }
}

// Function to sort array using Bubble Sort
void sort1(int *array, int size) {
    int sorted = 0; int *p;
    int k = size;
// Algorithm implementation using pointers
// Program continues until the array is sorted
    while (!sorted) {
        sorted = 1;

        // Iterating through the array using pointer arithmetic
        for ( p = array; p < array + k - 1; p++) {        //using pointers in place of loops and array references
            //Comparing adjacent elements and swapping them if they are in wrong order
            if (*p > *( p+ 1)) {
                sorted = 0;
                // Swapping elements using pointers
                int temp = *p;
                *p = *(p+ 1);
                *(p + 1) = temp;
            }
        }
        k--;   //decrementing the size of the array
    }
}

// Function to sort array using Selection Sort
void sort2(int *a, int size) {
    int *p, *j;

    // Algorithm implementation using pointers
    for ( p = a; p < a + size - 1; p++) {    // Selecting the smallest element in each cycle from the array
        int *minPosition =  p;
//Finding minimum element using pointer arithmetic
        for ( j = p+ 1; j < a + size; j++) {
            if (* j < *minPosition) {
                minPosition = j;
            }
        }

        // Swapping elements using pointers
        int temp = *minPosition;
        *minPosition = *p;
        *p  = temp;
    }
}



// Function to output elements of an array
void output(int *array, int size) {
    int *p;
//Outputting array elements using pointer arithmetic
    for (p = array; p < array + size; p++) {
        printf("%d ", *p);   // dereferencing pointer
    }
    printf("\n");
}

int main() {
    //
    int array1[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int array2[10];
    int size = 10;

    // Copying array1 to array2
    copy(array1, array2, size);

    // Sort array1 using Bubble Sort
    sort1(array1, size);
    printf("Sorted array1 through Bubble Sort: ");
    output(array1, size);

    // Sort array2 using Selection Sort
    sort2(array2, size);
    printf("Sorted array2 through Selection Sort: ");
    output(array2, size);

}

// Output

/*
Sorted array1 through Bubble Sort: 1 2 3 4 5 6 7 8 9 10
Sorted array2 through Selection Sort: 1 2 3 4 5 6 7 8 9 10
 */