// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to calculate the product of elements of an array except one and store it in that 
// particular index.
// ------------------------------------------------------------------------------------------------

#include<errno.h>
#include<malloc.h>
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
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE;
      }
   } while (!output);
   return validInt;
}

void PrintArray (int* array, int size) {
   for (int i = 0; i < size; i++)
      printf ("%d ", array[i]);
}

void ProductCalculator (int* array, int* answer, int size) {
   for (int i = 0; i < size; i++) {
      int prod = 1;
      for (int j = 0; j < size; j++)
         if (j != i)
            prod *= array[j];
      answer[i] = prod;
   }
}

int main () {
   int size, * array = NULL, * answer = NULL;
   do
      size = GetValidInteger ("Enter the size of the array: ");
   while (size <= 0);
   do {
      array = (int*)malloc (size * sizeof (int));
      answer = (int*)malloc (size * sizeof (int));
   } while (array == NULL || answer == NULL);
   for (int i = 0; i < size; i++)
      array[i] = GetValidInteger ("Enter the element: ");
   printf ("\nInput: ");
   PrintArray (array, size);
   ProductCalculator (array, answer, size);
   printf ("\nOutput: ");
   PrintArray (answer, size);
   return 0;
}