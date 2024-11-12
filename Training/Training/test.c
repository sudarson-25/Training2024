#pragma warning(disable:6385)
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// test.c
// Tests for selection sort and binary search
// Sudarson S
// ------------------------------------------------------------------------------------------------
#include"training.h"
#include<stdbool.h>
#include<stdio.h>
#include<string.h> // USED
#include<errno.h>
#include<malloc.h>
#include<stdlib.h>
#include <time.h>

/// <summary>Returns user inputs only if they are valid integers</summary>
static int GetValidInteger (char* prompt) {
   bool output;
   int num;
   do {
      char numberStr[4096], * result = NULL;
      printf ("%s", prompt);
      fgets (numberStr, sizeof (numberStr), stdin);
      result = strchr (numberStr, '\n');
      if (result == NULL) {
         while (getchar () != '\n');
         output = false;
      } else {
         errno = 0;
         char* endptr = NULL;
         num = strtol (numberStr, &endptr, 10);
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && numberStr[0] != ' ' &&
            numberStr[0] != '\t';
      }
      if (!output) printf ("Invalid Input\n");
   } while (output == false);
   return num;
}

/// <summary>Runs test cases for the sorting algorithm</summary>
static void SortTestCases () {
   srand ((unsigned int)time (NULL));
   // Creating random arrays of random lengths to test the algorithm
   int n = rand () % (20 - 1 + 1) + 1, ** jagged = malloc (n * sizeof (int*)),
      * size = malloc (n * sizeof (int));
   for (int i = 0; i < n; i++) {
      size[i] = rand () % (20 - 1 + 1) + 1; // Range [1,20]
      jagged[i] = malloc (sizeof (int) * size[i]);
      for (int j = 0; j < size[i]; j++) jagged[i][j] = rand () % (10000 + 10000 + 1) - 10000; // Range [-10000,10000]
   }
   printf ("\nTestCases\n~~~~~~~~~\nSelection Sort\n~~~~~~~~~~~~~");
   for (int i = 0; i < n; i++) {
      int k;
      char* dashes = ANSI_COLOR_YELLOW"----------------------------------------------------------------"
         "-----------------------------------------------"ANSI_COLOR_RESET;
      printf ("\n%s\nInput:    ", dashes);
      for (int j = 0; j < size[i]; j++) printf ("%d ", jagged[i][j]);
      SelectionSort (jagged[i], size[i]);
      printf ("\nSorted:   ");
      for (int j = 0; j < size[i]; j++) printf ("%d ", jagged[i][j]);
      for (k = 0; k < size[i] - 1 && jagged[i][k + 1] >= jagged[i][k]; k++);
      char* result = k == size[i] - 1 ? ANSI_COLOR_GREEN"Passed"ANSI_COLOR_RESET : ANSI_COLOR_RED"Failed"ANSI_COLOR_RESET;
      printf ("\nResult:   %s\n%s", result, dashes);
   }
   free (jagged);
   free (size);
}

/// <summary>Runs test cases for the searching algorithm</summary>
static void SearchTestCases () {
   int row0[] = { -5, 12, 19, 20, 21, 30 }, row1[] = { -5, 6 }, row2[] = { -12, -4, -4, 0, 3, 4, 4,
      4 }, row3[] = { -250, 15, 17, 46, 60 }, * jagged[] = { row0, row1, row2, row3 }, size[] = { 6,
      2, 8, 5 }, binSearchKey[] = { 20, 6, 4, 17 }, binExpected[] = { 3, 1, 5, 2 }, output;
   printf ("\nTestCases\n~~~~~~~~~\nBinary Search\n~~~~~~~~~~~~~");
   for (int i = 0; i < 4; i++) {
      char* dashes = ANSI_COLOR_YELLOW"----------------------------------------------------------------"
         "-----------------------------------------------"ANSI_COLOR_RESET;
      printf ("\n%s\nInput:      ", dashes);
      for (int j = 0; j < size[i]; j++) printf ("%d ", jagged[i][j]);
      printf ("\nSearch Key: %d", binSearchKey[i]);
      output = BinarySearch (jagged[i], size[i], binSearchKey[i]);
      char* result = output == binExpected[i] ? ANSI_COLOR_GREEN"Passed"ANSI_COLOR_RESET :
         ANSI_COLOR_RED"Failed"ANSI_COLOR_RESET;
      printf ("\nResult:     %s\n%s", result, dashes);
   }
}

/// <summary>Accepts user inputs</summary>
static int UserInputs (int** arr) {
   int arrSize;
   do {
      arrSize = GetValidInteger ("\nEnter an array size: ");
      if (arrSize <= 0) printf ("Invalid Input\n");
   } while (arrSize <= 0);
   do
      *arr = (int*)malloc ((arrSize) * sizeof (int));
   while (*arr == NULL);
   for (int i = 0; i < arrSize; i++) (*arr)[i] = GetValidInteger ("\nEnter an integer : ");
   return arrSize;
}

int main () {
   while (1) {
      int choice = GetValidInteger ("\n\nMenu\n~~~~\n1. Sort and Search\n2. Run Test Cases\n"
         "3. Exit\n\nEnter your choice: ");
      switch (choice) {
         case 1: {
               int key, arrSize, * arr = NULL;
               arrSize = UserInputs (&arr);
               printf ("\nUnsorted Array: ");
               for (int i = 0; i < arrSize; i++) printf ("%d ", arr[i]);
               SelectionSort (arr, arrSize);
               printf ("\nSorted Array: ");
               for (int i = 0; i < arrSize; i++) printf ("%d ", arr[i]);
               key = GetValidInteger ("\nEnter the element to be found: ");
               printf ("Element found at index: %d", BinarySearch (arr, arrSize, key));
               free (arr);
            }break;
         case 2:
            SortTestCases ();
            SearchTestCases ();
            break;
         case 3:
            return 0;
         default:
            printf ("Invalid Input");
      }
   }
}