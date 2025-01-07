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

int GCDCalculator (int num1, int num2) {
   if (num1 == 0) return num2;
   return GCDCalculator (num2 % num1, num1);
}

int LCMCalculator (int num1, int num2) {
   return (num1 / GCDCalculator (num1, num2)) * num2;
}

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
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE;
      }
   } while (!output);
   return validInt;
}

static void Testcases () {
   int inputs[][2] = { {1,2},{2,3},{3,5},{-45,30},{0,7} },
      expected[][2] = { {1,2},{1,6},{1,15},{15,90},{7,0} },
      size = sizeof (inputs) / sizeof (inputs[0]), i;
   for (i = 0; i < size && expected[i][0] == GCDCalculator (abs (inputs[i][0]), abs (inputs[i][1])) &&
      expected[i][1] == LCMCalculator (abs (inputs[i][0]), abs (inputs[i][1])); i++);
   printf (i == size ? "\n\nTestCases\n~~~~~~~~~\nPASSED\n" : "\n\nTestCases\n~~~~~~~~~\nFAILED\n");
}

int main () {
   int num1 = GetValidInteger ("Enter the number: "),
      num2 = GetValidInteger ("Enter the number: ");
   if (num1 != 0 || num2 != 0)
      printf ("GCD: %d\nLCM: %d", GCDCalculator (abs (num1), abs (num2)), LCMCalculator (abs (num1), abs (num2)));
   else
      printf ("Both can't be zero!");
   Testcases ();
   return 0;
}