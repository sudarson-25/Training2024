// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to swap 2 numbers.
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<errno.h>
#include<string.h>

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

void Swap (int* num1, int* num2) {
   *num1 = *num1 + *num2;
   *num2 = *num1 - *num2;
   *num1 = *num1 - *num2;
}

int main () {
   int num1 = GetValidInteger ("Enter a number (A): "),
      num2 = GetValidInteger ("Enter a number (B): ");
   if (num1 != num2) Swap (&num1, &num2);
   printf ("A: %d\nB: %d", num1, num2);
   return 0;
}