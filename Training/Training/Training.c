// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to print a diamond using an asterisk
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<errno.h>
#include<stdbool.h>
#include<stdio.h>
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
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && validInt > 0;
      }
   } while (!output);
   return validInt;
}

int main () {
   int rows = GetValidInteger ("Enter the number of rows: ") + 1;
   printf ("\n");
   for (int i = 0; i < 2 * rows - 1; i++) {
      int numSpaces = i < rows ? 2 * (rows - i) - 1 : 2 * (i - rows + 1) + 1;
      for (int j = 0; j < numSpaces; j++) printf (" ");
      for (int k = 0; k < 2 * rows - numSpaces; k++) printf ("* ");
      printf ("\n");
   }
   return 0;
}