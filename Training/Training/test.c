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

/// <summary>Checks if a given input is a valid integer</summary>
void IsValidInteger (char* prompt, int* num) {
   bool output;
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
         *num = strtol (numberStr, &endptr, 10);
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && numberStr[0] != ' ' &&
            numberStr[0] != '\t';
      }
      if (output == false) printf ("Invalid Input\n");
   } while (output == false);
}

/// <summary>Runs test cases for the sorting algorithm</summary>
void SortTestCases () {
   srand ((unsigned int)time (NULL));
   // Range of n [1,20]
   int n = rand () % (20 - 1 + 1) + 1, ** jagged = malloc (n * sizeof (int*)),
      * size = malloc (n * sizeof (int));
   for (int i = 0; i < n; i++) {
      size[i] = rand () % (20 - 1 + 1) + 1; // Range [1,20]
      jagged[i] = malloc (sizeof (int) * size[i]);
      for (int j = 0; j < size[i]; j++) {
         jagged[i][j] = rand () % (10000 + 10000 + 1) - 10000; // Range [-10000,10000]
      }
   }
   printf ("\nTestCases\n~~~~~~~~~\nSelection Sort\n~~~~~~~~~~~~~");
   for (int i = 0; i < n; i++) {
      int k;
      printf (ANSI_COLOR_YELLOW"\n----------------------------------------------------------------"
         "-----------------------------------------"ANSI_COLOR_RESET"\nInput:    ");
      for (int j = 0; j < size[i]; j++) printf ("%d ", jagged[i][j]);
      SelectionSort (jagged[i], size[i]);
      printf ("\nSorted:   ");
      for (int j = 0; j < size[i]; j++) printf ("%d ", jagged[i][j]);
      for (k = 0; k < size[i] - 1; k++)
         if (jagged[i][k + 1] < jagged[i][k]) {
            printf ("\nResult:   "ANSI_COLOR_RED"Failed\n"ANSI_COLOR_YELLOW"----------------------"
               "-----------------------------------------------------------------------------------"
               ANSI_COLOR_RESET);
            break;
         }
      if (k == size[i] - 1) printf ("\nResult:   "ANSI_COLOR_GREEN"Passed\n"ANSI_COLOR_YELLOW"----"
         "----------------------------------------------------------------------------------------"
         "-------------"ANSI_COLOR_RESET);
   }
   free (jagged);
   free (size);
}

/// <summary>Runs test cases for the searching algorithm</summary>
void SearchTestCases () {
   int row0[] = { 20,19,-5,30,21,12 }, row1[] = { -5, 6 }, row2[] = { 0,-12,3,4,-4,4,-4,4 }, row3[] = { -250, 60, 46, 17, 15 },
      * jagged[] = { row0, row1, row2, row3 }, size[] = { 6, 2, 8, 5 }, binSearchKey[] = { 20, 6, 4, 17 },
      binExpected[] = { 3, 1, 5, 2 }, output;
   printf ("\nTestCases\n~~~~~~~~~\nBinary Search\n~~~~~~~~~~~~~");
   for (int i = 0; i < 4; i++) {
      printf (ANSI_COLOR_YELLOW"\n----------------------------------------------------------------"
         "-----------------------------------------"ANSI_COLOR_RESET"\nInput:          ");
      for (int j = 0; j < size[i]; j++) printf ("%d ", jagged[i][j]);
      SelectionSort (jagged[i], size[i]);
      printf ("\nSorted:         ");
      for (int j = 0; j < size[i]; j++) printf ("%d ", jagged[i][j]);
      printf ("\nSearch Key:     %d\nExpected Index: %d\nOutput Index:"
         "   %d", binSearchKey[i], binExpected[i], output = BinarySearch (jagged[i], size[i], binSearchKey[i]));
      printf (output == binExpected[i] ? "\nResult:         "ANSI_COLOR_GREEN"Passed\n"ANSI_COLOR_RESET :
         "\nResult:         "ANSI_COLOR_RED"Failed\n"ANSI_COLOR_RESET);
      printf (ANSI_COLOR_YELLOW"------------------------------------------------------------------"
         "---------------------------------------"ANSI_COLOR_RESET);
   }
}

/// <summary>Accepts user inputs</summary>
void UserInputs (int** arr, int* arrSize) {
   do {
      IsValidInteger ("\nEnter an array size: ", arrSize);
      if (*arrSize <= 0) printf ("Invalid Input\n");
   } while (*arrSize <= 0);
   do
      *arr = (int*)malloc ((*arrSize) * sizeof (int));
   while (*arr == NULL);
   for (int i = 0; i < *arrSize; i++) {
      int element;
      IsValidInteger ("\nEnter an integer : ", &element);
      (*arr)[i] = element;
   }
}

int main () {
   while (1) {
      int choice;
      IsValidInteger ("\n\nMenu\n~~~~\n1. Sort and Search\n2. Run Test Cases\n"
         "3. Exit\n\nEnter your choice: ", &choice);
      switch (choice) {
         case 1: {
               int key, arrSize, * arr = NULL;
               UserInputs (&arr, &arrSize);
               printf ("\nUnsorted Array: ");
               for (int i = 0; i < arrSize; i++) printf ("%d ", arr[i]);
               SelectionSort (arr, arrSize);
               printf ("\nSorted Array: ");
               for (int i = 0; i < arrSize; i++) printf ("%d ", arr[i]);
               IsValidInteger ("\nEnter the element to be found: ", &key);
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