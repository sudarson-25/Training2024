// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to check if a given number is prime or not.
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h> // USED
#include<errno.h>

#define PRIME -1
#define COMPOSITE -2
#define NEITHER -3

/// <summary>Returns user inputs only if they are valid positive integers</summary>
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

/// <summary>Returns if a number is prime, composite or neither</summary>
int PrimeChecker (int num) {
   if (num == 1) return NEITHER;
   if (num == 2) return PRIME;
   for (int i = 2; i <= num / 2; i++)
      if (num % i == 0) return COMPOSITE;
   return PRIME;
}

int main () {
   int num = GetValidInteger ("Enter a number: "),
      result = PrimeChecker (num);
   printf (result == PRIME ? "Prime" : result == NEITHER ? "Neither prime nor composite" : "Composite");
   return 0;
}