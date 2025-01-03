// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to calculate the GCD and LCM of 2 numbers.
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<errno.h>
#include<stdbool.h>
#include<stdio.h>
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
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && validInt > 0;
      }
   } while (!output);
   return validInt;
}

int GCDCalculator (int num1, int num2) {
   if (num1 == 0) return num2;
   return GCDCalculator (num2 % num1, num1);
}

int LCMCalculator (int num1, int num2) {
   return (num1 / GCDCalculator (num1, num2)) * num2;
}

int main () {
   int num1 = GetValidInteger ("Enter the number: "),
      num2 = GetValidInteger ("Enter the number: ");
   printf ("GCD: %d\nLCM: %d", GCDCalculator (num1, num2), LCMCalculator (num1, num2));
   return 0;
}