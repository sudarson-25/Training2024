// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to swap 2 indices.
// ------------------------------------------------------------------------------------------------

#include<errno.h>
#include <malloc.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

static int GetValidInteger (char* prompt, int n) {
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
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && validInt >= 0 && validInt < n;
      }
   } while (!output);
   return validInt;
}

void Swap (int* array, int idx1, int idx2) {
   array[idx1] = array[idx1] + array[idx2];
   array[idx2] = array[idx1] - array[idx2];
   array[idx1] = array[idx1] - array[idx2];
}

void PrintArray (int* array, int n) {
   for (int i = 0; i < n; i++) printf ("%d ", array[i]);
}

int main () {
   srand ((unsigned int)time (NULL));
   int n = rand () % (20 - 1 + 1) + 1, // Range [1, 20]
      * array = malloc (n * sizeof (int)), idx1, idx2;
   if (array == NULL) {
      printf ("Memory allocation failed!\n");
      return 1;
   }
   for (int i = 0; i < n; i++)
      array[i] = rand () % (10000 + 10000 + 1) - 10000; // Range [-10000, 10000]
   PrintArray (array, n);
   idx1 = GetValidInteger ("\nEnter first index: ", n);
   idx2 = GetValidInteger ("\nEnter the second index: ", n);
   if (idx1 != idx2) Swap (array, idx1, idx2);
   PrintArray (array, n);
   free (array);
   return 0;
}