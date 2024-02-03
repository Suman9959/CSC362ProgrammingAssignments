#include <stdio.h>



int main() {
    int i;



        // Assembly code for primality check and output
        __asm {
            mov eax, 3
            top: cmp eax, 1001
            mov ebx, eax
            jg done
            mul eax
            add eax, 2
            mov isPrime, 1

            mov esi, 2

            checkprime1:
            mov eax, ebx
            div esi
            cmp edx, 0
            je notPrime1

            inc esi
            cmp esi, ebx
            jg prime1
            jmp top

            notPrime1:
            mov isPrime, 0
            jump endPrimeCheck1


            prime1:
            mov eax
                prime1:
            // Computing i^2 - 2
                sub eax, 4         // eax = i^2 - 2
                mov ebx, eax       // ebx = i^2 - 2 for prime check

            // Check for primality of i^2 - 2
                mov esi, 2         // esi = divisor starting at 2

                checkPrime2:
                mov eax, ebx       // eax = i^2 - 2 (numerator)
                xor edx, edx       // Clear edx for division

            // Check if esi divides i^2 - 2 evenly
                div esi
                cmp edx, 0         // Check remainder
                je notPrime2       // If remainder is 0, not a prime number

                inc esi            // Increment divisor
                cmp esi, ebx       // Compare divisor with i^2 - 2
                jg prime2          // If divisor > i^2 - 2, it's prime
                jmp checkPrime2    // Otherwise, continue checking

                notPrime2:
                mov isPrime, 0     // i^2 - 2 is not prime

                prime2:
                cmp isPrime, 1     // Check if both i^2 + 2 and i^2 - 2 are prime
                jne endPrimeCheck2 // If any of them is not prime, skip output

            // Output the number i if both conditions are satisfied
                mov eax, ecx       // eax = i
                push eax           // Prepare for printf
                push offset format // Push the format string for printf
                call printf        // Call printf to output i
                add esp, 8         // Clean up the stack after printf

                endPrimeCheck2:
            // Update the loop counter
                add ecx, 2         // Increment i by 2 (odd numbers only)
                cmp ecx, 1001      // Check if i > 1001
                jle oddLoop        // Continue loop if i <= 1001

            // End of assembly code
        }

    printf("Numbers between 3 and 1001 satisfying the conditions:\n");
}
