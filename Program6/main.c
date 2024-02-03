/*Name: Suman Bhandari
Program 6

   This assembly program finds the number with the maximum occurrences in the given array.
   The array 'array' is initialized with a set of integers, and 'n' defines the total number
   of elements in the array.

  This program involves two nested loops. The outer loop iterates through each item in the array, while the inner loop scans the rest of the array to count how many times the current number appears.
   Once the inner loop reaches the end of the array, it checks if the count of occurrences is a new maximum. If it is, the program stores this number along with its occurrences

   The algorithm involves iterating through the array to determine the number with the highest
   count of occurrences. It initializes variables to track the maximum count and the number
   associated with it. The outer loop indexes each element in the array while the inner loop
   counts occurrences for each element by comparing it with the rest of the array.

   It stores the number with the maximum occurrences in 'maxNumber' and the corresponding count
   in 'maxCount'.It outputs the result displaying the number and its count.

   Assembly code is inside __asm{ ..}. Everything except entering array and no. of elements in array is done in assembly code.

*/


#include <stdio.h>
int main() {

    int array[] = { 5, 3, 8, 9, 3, 4, 1, 8, 2, 3, 9, 5, 6, 5, 5, 8, 7, 3, 0, 1, 3, 8, 5, 3, 3, 9, 4, 2, 3, 8, 5, 6, 2, 3, 4, 1, 3, 8, 5 }
    ;

    int n = 40; // Number of elements in the array

    int maxNumber, maxCount; // Variables to store the number and its count

    __asm {
            mov  eax, 0        // eax, Outer loop index is set to 0
            mov maxCount, 0        // Initializing maxCount to 0
            mov maxNumber, 0       //  Initializing maxNumber to 0

        // Outer loop to iterate through each element in the array
            outer_loop:
            cmp     eax, n           // Check if outer loop index reached the end of the array
            jge     done_outer_loop  // If so, exit outer loop and jump to done_outer_loop

        // Load current number from the array
            mov     edx, array[eax * 4]  // Load current number into temporary register,
        //eax*4 as length of each int data is 4-byte
            mov     ebx, eax
            mov ecx, 1    // Initialize count for the current number to 1
            inner_loop :
            inc ebx                // Move to the next element in the array
            cmp     ebx, n           // Check if inner loop index reached the end of the array
            jge     done_inner_loop  // If so, exit inner loop and jump to done_inner_loop

            cmp edx, array[ebx * 4] // Compare the current number with array element
            jne     no_increment        // If not equal, skip incrementing the count and jump to no_increment

            inc     ecx              // Increment count if numbers match
            no_increment :
            jmp     inner_loop       // Repeat inner loop

            done_inner_loop :
        // ecx is holding cuurent count number
            cmp     ecx, maxCount    // Check if the count is greater than the max count
            jle     next_Step   // If not, skip updating maxCount and maxNumber

            mov     maxCount, ecx    // Update maxCount with the current count
            mov     maxNumber, edx   // Update maxNumber with the current number

            next_Step :
            inc     eax              // Increment outer loop index
            jmp     outer_loop       // Repeat outer loop

            done_outer_loop :

    }
    // Output the number with the maximum occurrences in the array
    printf("%d occurs %d times\n", maxNumber, maxCount);
    return 0;
}

//Output
/*
*Sample test 1 (Array 2)
3 occurs 10 times

Sample Test 2  (Array 3)
26 occurs 7 times
*/