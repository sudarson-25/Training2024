#define _CRT_SECURE_NO_WARNINGS  1
#include <stdio.h>
#include<string.h>
/* Demo program to implement a Mealy machine.
*  This machine detects a pattern 0110 or 1101 in an input stream.
*/

// Define states of the Mealy machine
typedef enum {
   S0,  // Initial state
   S1,  // After '0'
   S2,  // After '01'
   S3,  // After '011'
   A,   // After '110'
   B,   // After '11'
   C    // After '1'
} State;

// Function to get the next state and output based on the current state and input
State nextMealyState (State currentState, int input, int* output) {
   switch (currentState) {
      case S0:
         if (input == 0) {
            *output = 0;
            return S1;  // Transition to S1 after '0'
         } else {
            *output = 0;
            return C;  // Transition to C after '1'
         }
      case S1:
         if (input == 1) {
            *output = 0;
            return S2;  // Transition to S2 after '01'
         } else {
            *output = 0;
            return S1;  // Stay in S1 if input is '0'
         }
      case S2:
         if (input == 1) {
            *output = 0;
            return S3;  // Transition to S3 after '011'
         } else {
            *output = 0;
            return S1;  // Return to S1 if input is '0'
         }
      case S3:
         if (input == 0) {
            *output = 1;  // Output '1' upon seeing '0110'
            return A;  // Move to A after recognizing '0110'
         } else {
            *output = 0;
            return B; // Transition to B after '110'
         }
      case A:
         if (input == 1) {
            *output = 1;  // Output '1' upon seeing '1101'
            return S2;  // Move to S2 after recognizing '1101'
         } else {
            *output = 0;
            return S1;  // Return to S1 if input is '0'
         }
      case B:
         if (input == 0) {
            *output = 0;
            return A;  // Transition to A after '110'
         } else {
            *output = 0;
            return B;  // Stay in B if input is '1'
         }
      case C:
         if (input == 0) {
            *output = 0;
            return S1;  // Return to S1 if input is '0'
         } else {
            *output = 0;
            return B;  // Transition to B after '11'
         }
   }
   return S0;  // Default return to initial state
}

static int mealy (char* inputPath, char* outputPath) {
   State currentState = S0;  // Start in initial state
   int output = 0;
   FILE* ifp = fopen (inputPath, "r");
   FILE* tfp = fopen ("tempOut.txt", "w");
   if (ifp == NULL) printf ("Input file does not exist");
   else {
      char ch = fgetc (ifp);
      if (ch == EOF)
         printf ("File has no content!");
      else {
         while (ch != EOF && (ch == '0' || ch == '1')) {
            currentState = nextMealyState (currentState, (int)ch - 48, &output);
            fprintf (tfp, "%d", output);
            ch = fgetc (ifp);
         }
      }
      fclose (ifp);
      fclose (tfp);
   }
   return 0;
}

void main (int argc, char* argv[]) {
   char inputPath[260], outputPath[260];
   strcpy (inputPath, argv[1]);
   strcpy (outputPath, argv[2]);
   mealy (inputPath, outputPath);
}