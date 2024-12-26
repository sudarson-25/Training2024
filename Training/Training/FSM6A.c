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
   *output = 0;
   switch (currentState) {
      case S0:
         // Transition to S1 after '0'
         // Transition to C after '1'
         return input == 0 ? S1 : C;
      case S1:
         // Transition to S2 after '01'
         // Stay in S1 if input is '0'
         return input == 1 ? S2 : S1;
      case S2:
         // Transition to S3 after '011'
         // Return to S1 if input is '0'
         return input == 1 ? S3 : S1;
      case S3:
         // Output '1' upon seeing '0110'
         // Move to A after recognizing '0110'
         // Transition to B after '110'
         if (input == 0) {
            *output = 1;
            return A;
         } else return B;
      case A:
         // Output '1' upon seeing '1101'
         // Move to S2 after recognizing '1101'
         // Return to S1 if input is '0'
         if (input == 1) {
            *output = 1;
            return S2;
         } else return S1;
      case B:
         // Transition to A after '110'
         // Stay in B if input is '1'
         return input == 0 ? A : B;
      case C:
         // Return to S1 if input is '0'
         // Transition to B after '11'
         return input == 0 ? S1 : B;
      default:
         return S0;  // Default return to initial state
   }
}

static int mealy (char* inputPath, char* outputPath) {
   State currentState = S0;  // Start in initial state
   int output = 0;
   FILE* ifp = fopen (inputPath, "r");
   FILE* tfp = fopen (outputPath, "w");
   if (ifp == NULL) printf ("Input file does not exist");
   else {
      char ch = fgetc (ifp);
      if (ch == EOF) printf ("File has no content!");
      else
         while (ch != EOF && (ch == '0' || ch == '1')) {
            currentState = nextMealyState (currentState, (int)ch - '0', &output);
            fprintf (tfp, "%d", output);
            ch = fgetc (ifp);
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