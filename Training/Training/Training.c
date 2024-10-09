// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to to perform Selection Sort and Binary Search
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<stdbool.h>
#include<errno.h>
#include <string.h>
#include<malloc.h>
#include<stdlib.h>

#define column 8
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/// <summary>Function implementing selection sort logic </summary>
void SelectionSort (int* arr, int n) {
   for (int i = 0; i < n - 1; i++) {
      int minInd = i;
      // Iterate through the unsorted portion to find the actual minimum
      for (int j = i + 1; j < n; j++)
         if (arr[j] < arr[minInd])
            // Update minInd if a smaller element is found
            minInd = j;
      // If a new minimum is found, swap it with the element at index i
      if (minInd != i) {
         int temp = arr[i];
         arr[i] = arr[minInd];
         arr[minInd] = temp;
      }
   }
}

/// <summary>Function implementing binary search logic </summary>
int BinarySearch (int* arr, int arrSize, int key) {
   int low = 0, high = arrSize - 1;
   while (low <= high) {
      int mid = low + (high - low) / 2;
      // Check if key is present at mid, and check for first occurance
      if (arr[mid] == key)
         while (arr[--mid] != key)
            return mid + 1;
      else if (arr[mid] < key)
         low = mid + 1;
      else
         high = mid - 1;
   }
   // If element was not present
   return -1;
}

/// <summary>Function to check if the given input is a valid integer</summary>
bool IsValidInteger (char* number, int* num) {
   errno = 0;
   char* endptr = NULL;
   *num = strtol (number, &endptr, 10);
   return endptr == number || *endptr != '\n' || errno == ERANGE || number[0] == ' ' ||
      number[0] == '\t' ?
      false : true;
}

/// <summary>Function to drain the unassigned inputs from stdin</summary>
void BufferDrain () {
   while (getchar () != '\n');
}

/// <summary>Function to accept user inputs</summary>
void UserInputs (int** arr, int* arrSize) {
   char arrSizeStr[13], * result = NULL;
   bool sizeFlag;
   do {
      sizeFlag = false;
      printf ("\nEnter an array size: ");
      fgets (arrSizeStr, sizeof (arrSizeStr), stdin);
      result = strchr (arrSizeStr, '\n');
      if (result == NULL) {
         printf ("Enter a valid array size!\n");
         sizeFlag = true;
         BufferDrain ();
      } else {
         if (IsValidInteger (arrSizeStr, arrSize) && *arrSize > 0) {
            do {
               *arr = (int*)malloc ((*arrSize) * sizeof (int));
            } while (*arr == NULL);
            char elementStr[13], * elementResult = NULL;
            for (int i = 0; i < *arrSize; i++) {
               bool flag;
               do {
                  flag = false;
                  printf ("\nEnter an integer: ");
                  fgets (elementStr, sizeof (elementStr), stdin);
                  elementResult = strchr (elementStr, '\n');
                  if (elementResult == NULL) {
                     printf ("Enter a valid integer!\n");
                     flag = true;
                     BufferDrain ();
                  } else {
                     int element;
                     if (IsValidInteger (elementStr, &element))
                        (*arr)[i] = element;
                     else {
                        printf ("Enter a valid integer!\n");
                        flag = true;
                     }
                  }
               } while (flag == true);
            }
         } else {
            printf ("\nEnter a valid array size");
            sizeFlag = true;
         }
      }
   } while (sizeFlag == true);
}

/// <summary>Function to print the array elements</summary>
void printArray (int* arr, int n) {
   for (int i = 0; i < n; i++)
      printf ("%d ", arr[i]);
}

/// <summary>Function to run test cases</summary>
void TestCases () {
   int inputs[][column] = { {0,12,3,4,4,4,4,4},{-98,45,2,1,3,4,0,0},{6,7,8,9,-4,-5,-9,0} },
      binSearchKey[] = { 12,4,-4 }, binExpected[] = { 7,6,2 },
      sortExpected[][column] = { { 0,3,4,4,4,4,4,12},{-98,0,0,1,2,3,4,45 },{-9,-5,-4,0,6,7,8,9 } },
      n = sizeof (inputs) / sizeof (inputs[0]);
   printf ("\nTestCases\n~~~~~~~~~");
   for (int i = 0; i < n; i++) {
      int output, flag = 0;
      printf (ANSI_COLOR_YELLOW"\n----------------------------------------------------------------"
              "-----------------------------------------"ANSI_COLOR_RESET"\nSelection Sort\n~~~~~~"
              "~~~~~~~\nInput:    ");
      printArray (inputs[i], column);
      printf ("\nExpected: ");
      printArray (sortExpected[i], column);
      SelectionSort (inputs[i], column);
      printf ("\nSorted:   ");
      printArray (inputs[i], column);
      for (int j = 0; j < column; j++)
         if (inputs[i][j] == sortExpected[i][j])
            flag++;
      flag == column ?
         printf ("\nResult:   "ANSI_COLOR_GREEN"Passed\n"ANSI_COLOR_RESET) :
         printf ("\nResult:   "ANSI_COLOR_RED"Failed\n"ANSI_COLOR_RESET);
      printf ("\nBinary Search\n~~~~~~ ~~~~~~\nSearch Key:     %d\nExpected Index: %d\nOutput Inde"
              "x:   %d", binSearchKey[i], binExpected[i], output = BinarySearch (inputs[i], 8, binSearchKey[i]));
      output == binExpected[i] ?
         printf ("\nResut:          "ANSI_COLOR_GREEN"Passed\n"ANSI_COLOR_RESET) :
         printf ("\nResult:         "ANSI_COLOR_RED"Failed\n"ANSI_COLOR_RESET);
      printf (ANSI_COLOR_YELLOW"------------------------------------------------------------------"
              "---------------------------------------"ANSI_COLOR_RESET);
   }
   printf ("\n");
}

int main () {
   char choice[3], * result = NULL;
   while (1) {
      printf ("Menu\n~~~~\n1. Selection Sort\n2. Binary Search\n3. Run Test Cases\n"
              "4. Exit\n\nEnter your choice: ");
      fgets (choice, sizeof (choice), stdin);
      result = strchr (choice, '\n');
      if (result == NULL) {
         printf ("Invalid Choice!\n");
         BufferDrain ();
      } else
         switch (choice[0]) {
            int arrSize, * arr = NULL;
            case '1': {
                  UserInputs (&arr, &arrSize);
                  printf ("Unsorted Array: ");
                  printArray (arr, arrSize);
                  SelectionSort (arr, arrSize);
                  printf ("\nSorted Array: ");
                  printArray (arr, arrSize);
                  free (arr);
               }break;
            case '2': {
                  char keyStr[13];
                  bool keyFlag;
                  UserInputs (&arr, &arrSize);
                  printf ("Unsorted Array: ");
                  printArray (arr, arrSize);
                  SelectionSort (arr, arrSize);
                  printf ("\nSorted Array: ");
                  printArray (arr, arrSize);
                  do {
                     keyFlag = false;
                     printf ("\nEnter the element to be found: ");
                     fgets (keyStr, sizeof (keyStr), stdin);
                     result = strchr (keyStr, '\n');
                     if (result == NULL) {
                        printf ("Enter a valid element!\n");
                        keyFlag = true;
                        BufferDrain ();
                     } else {
                        int key;
                        if (IsValidInteger (keyStr, &key))
                           printf ("Element found at index: %d\n", BinarySearch (arr, arrSize, key));
                        else {
                           printf ("Enter a valid element!\n");
                           keyFlag = true;
                        }
                     }
                  } while (keyFlag == true);
                  free (arr);
               }break;
            case '3':
               TestCases ();
               break;
            case '4':
               return 0;
            default:
               printf ("Invalid Choice\n");
         }
      printf ("\n");
   }
}