// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Executes the main function
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
      char numberStr[13], * result = NULL;
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
         output = endptr == numberStr || *endptr != '\n' || errno == ERANGE || numberStr[0] == ' ' ||
            numberStr[0] == '\t' ? false : true;
      }
      if (output == false)
         printf ("Invalid Input\n");
   } while (output == false);
}

/// <summary>Accepts user inputs</summary>
void UserInputs (int** arr, int* arrSize) {
   do {
      IsValidInteger ("\nEnter an array size: ", arrSize);
      if (*arrSize <= 0)
         printf ("Invalid Input\n");
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

/// <summary>Prints the array elements</summary>
void PrintArray (int* arr, int n) {
   for (int i = 0; i < n; i++)
      printf ("%d ", arr[i]);
}

/// <summary>Runs test cases</summary>
void TestCases () {
   int inputs[][8] = { {0,12,3,4,4,4,4,4},{-98,45,2,1,3,4,0,0},{6,7,8,9,-4,-5,-9,0},{0,0,0,0,0,0,0,0} }, j,
      binSearchKey[] = { 12,4,-4,6 }, binExpected[] = { 7,6,2,-1 }, n = sizeof (inputs) / sizeof (inputs[0]),
      sortExpected[][8] = { { 0,3,4,4,4,4,4,12},{-98,0,0,1,2,3,4,45 },{-9,-5,-4,0,6,7,8,9 },{0,0,0,0,0,0,0,0} };
   printf ("\nTestCases\n~~~~~~~~~");
   for (int i = 0; i < n; i++) {
      int output, flag = 0;
      printf (ANSI_COLOR_YELLOW"\n----------------------------------------------------------------"
              "-----------------------------------------"ANSI_COLOR_RESET"\nSelection Sort\n~~~~~~"
              "~~~~~~~\nInput:    ");
      PrintArray (inputs[i], 8);
      printf ("\nExpected: ");
      PrintArray (sortExpected[i], 8);
      SelectionSort (inputs[i], 8);
      printf ("\nSorted:   ");
      PrintArray (inputs[i], 8);
      for (j = 0; j < 8; j++)
         if (inputs[i][j] != sortExpected[i][j]) {
            printf ("\nResult:   "ANSI_COLOR_RED"Failed\n"ANSI_COLOR_RESET);
            break;
         }
      if (j == 8)
         printf ("\nResult:   "ANSI_COLOR_GREEN"Passed\n"ANSI_COLOR_RESET);
      printf ("\nBinary Search\n~~~~~~ ~~~~~~\nSearch Key:     %d\nExpected Index: %d\nOutput Index:"
              "   %d", binSearchKey[i], binExpected[i], output = BinarySearch (inputs[i], 8, binSearchKey[i]));
      printf (output == binExpected[i] ? "\nResult:         "ANSI_COLOR_GREEN"Passed\n"ANSI_COLOR_RESET :
              "\nResult:         "ANSI_COLOR_RED"Failed\n"ANSI_COLOR_RESET);
      printf (ANSI_COLOR_YELLOW"------------------------------------------------------------------"
              "---------------------------------------"ANSI_COLOR_RESET);
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
               PrintArray (arr, arrSize);
               SelectionSort (arr, arrSize);
               printf ("\nSorted Array: ");
               PrintArray (arr, arrSize);
               IsValidInteger ("\nEnter the element to be found: ", &key);
               printf ("Element found at index: %d", BinarySearch (arr, arrSize, key));
               free (arr);
            }break;
         case 2:
            TestCases ();
            break;
         case 3:
            return 0;
         default:
            printf ("Invalid Input");
      }
   }
}