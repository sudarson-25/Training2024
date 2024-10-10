// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Implements selection sort and binary search
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include"header.h"
#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<malloc.h>
#include<stdlib.h>

/// <summary>Checks if a given input is a valid integer</summary>
void IsValidInteger (char* prompt, int* num) {
   bool output;
   do {
      char arrSizeStr[13], * result = NULL;
      printf ("%s", prompt);
      fgets (arrSizeStr, sizeof (arrSizeStr), stdin);
      result = strchr (arrSizeStr, '\n');
      if (result == NULL) {
         while (getchar () != '\n');
         output = false;
      } else {
         errno = 0;
         char* endptr = NULL;
         *num = strtol (arrSizeStr, &endptr, 10);
         output = endptr == arrSizeStr || *endptr != '\n' || errno == ERANGE || arrSizeStr[0] == ' ' ||
            arrSizeStr[0] == '\t' ? false : true;
      }
      if (output == false)
         printf ("Invalid Input\n\n");
   } while (output == false);
}

/// <summary>Accepts user inputs</summary>
void UserInputs (int** arr, int* arrSize) {
   printf ("\n");
   do {
      IsValidInteger ("Enter an array size: ", arrSize);
      if (*arrSize <= 0)
         printf ("Invalid Input\n\n");
   } while (*arrSize <= 0);
   do {
      *arr = (int*)malloc ((*arrSize) * sizeof (int));
   } while (*arr == NULL);
   printf ("\n");
   for (int i = 0; i < *arrSize; i++) {
      int element;
      IsValidInteger ("Enter an integer : ", &element);
      (*arr)[i] = element;
   }
}

/// <summary>Prints the array elements</summary>
void printArray (int* arr, int n) {
   for (int i = 0; i < n; i++)
      printf ("%d ", arr[i]);
}

/// <summary>Runs test cases</summary>
void TestCases () {
   int inputs[][8] = { {0,12,3,4,4,4,4,4},{-98,45,2,1,3,4,0,0},{6,7,8,9,-4,-5,-9,0} },
      binSearchKey[] = { 12,4,-4 }, binExpected[] = { 7,6,2 }, n = sizeof (inputs) / sizeof (inputs[0]),
      sortExpected[][8] = { { 0,3,4,4,4,4,4,12},{-98,0,0,1,2,3,4,45 },{-9,-5,-4,0,6,7,8,9 } };
   printf ("\nTestCases\n~~~~~~~~~");
   for (int i = 0; i < n; i++) {
      int output, flag = 0;
      printf (ANSI_COLOR_YELLOW"\n----------------------------------------------------------------"
              "-----------------------------------------"ANSI_COLOR_RESET"\nSelection Sort\n~~~~~~"
              "~~~~~~~\nInput:    ");
      printArray (inputs[i], 8);
      printf ("\nExpected: ");
      printArray (sortExpected[i], 8);
      SelectionSort (inputs[i], 8);
      printf ("\nSorted:   ");
      printArray (inputs[i], 8);
      for (int j = 0; j < 8; j++)
         if (inputs[i][j] == sortExpected[i][j])
            flag++;
      flag == 8 ?
         printf ("\nResult:   "ANSI_COLOR_GREEN"Passed\n"ANSI_COLOR_RESET) :
         printf ("\nResult:   "ANSI_COLOR_RED"Failed\n"ANSI_COLOR_RESET);
      printf ("\nBinary Search\n~~~~~~ ~~~~~~\nSearch Key:     %d\nExpected Index: %d\nOutput Index:"
              "   %d", binSearchKey[i], binExpected[i], output = BinarySearch (inputs[i], 8, binSearchKey[i]));
      printf (output == binExpected[i] ?
              "\nResult:         "ANSI_COLOR_GREEN"Passed\n"ANSI_COLOR_RESET :
              "\nResult:         "ANSI_COLOR_RED"Failed\n"ANSI_COLOR_RESET);
      printf (ANSI_COLOR_YELLOW"------------------------------------------------------------------"
              "---------------------------------------"ANSI_COLOR_RESET);
   }
}

int main () {
   int choice;
   while (1) {
      IsValidInteger ("Menu\n~~~~\n1. Selection Sort\n2. Binary Search\n3. Run Test Cases\n"
                      "4. Exit\n\nEnter your choice: ", &choice);
      switch (choice) {
         int arrSize, * arr = NULL;
         case 1: {
               UserInputs (&arr, &arrSize);
               printf ("\nUnsorted Array: ");
               printArray (arr, arrSize);
               SelectionSort (arr, arrSize);
               printf ("\nSorted Array: ");
               printArray (arr, arrSize);
               free (arr);
            }break;
         case 2: {
               int key;
               UserInputs (&arr, &arrSize);
               printf ("\nUnsorted Array: ");
               printArray (arr, arrSize);
               SelectionSort (arr, arrSize);
               printf ("\nSorted Array: ");
               printArray (arr, arrSize);
               printf ("\n\n");
               IsValidInteger ("Enter the element to be found: ", &key);
               printf ("Element found at index: %d", BinarySearch (arr, arrSize, key));
               free (arr);
            }break;
         case 3:
            TestCases ();
            break;
         case 4:
            return 0;
         default:
            printf ("Invalid Input");
      }
      printf ("\n\n");
   }
}