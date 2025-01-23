// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to print Pascal's Triangle.
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<errno.h>
#include<stdbool.h>
#include<stdlib.h>
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
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && validInt > 0 && validInt <= 30;
      }
   } while (!output);
   return validInt;
}

int main () {
   int rows = GetValidInteger ("Enter the number of rows (1<=n<=30): ");
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < rows - i - 1; j++) printf (" ");
      int val = 1;
      for (int k = 0; k <= i; k++) {
         printf ("%d ", val);
         val = val * (i - k) / (k + 1);
      }
      printf ("\n");
   }
   return 0;
}