// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to print the factorial for a given number.
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
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && validInt >= 0 && validInt <= 20;
      }
   } while (!output);
   return validInt;
}

long long int Factorial (int num) {
   long long int fact = num;
   return num == 0 ? 1 : (fact *= Factorial (num - 1));
}

int main () {
   printf ("%lld", Factorial (GetValidInteger ("Enter a number (0<=N<=20): ")));
   return 0;
}