// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to display the fibonacci series.
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<stdbool.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

/// <summary>Returns user inputs only if they are valid integers</summary>
static int GetValidInteger (char* prompt) {
   bool output;
   int validInt;
   do {
      char numberStr[4096];
      printf ("%s", prompt);
      fgets (numberStr, sizeof (numberStr), stdin);
      if (output = strchr (numberStr, '\n') != NULL) {
         errno = 0;
         char* endptr = NULL;
         validInt = strtol (numberStr, &endptr, 10);
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && validInt > 0 && validInt < 48;
      }
   } while (!output);
   return validInt;
}

void Fibonacci (int num) {
   int prev1 = -1, prev2 = 1, curr;
   for (int i = 0; i < num; i++) {
      curr = prev1 + prev2;
      printf ("\n%d ", curr);
      prev1 = prev2;
      prev2 = curr;
   }
}

int main () {
   int num = GetValidInteger ("Enter the number of terms (0<N<48): ");
   Fibonacci (num);
   return 0;
}