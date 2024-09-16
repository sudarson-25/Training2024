// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to check for palindrome of a string or an integer
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<ctype.h>
#include<errno.h>
#include <limits.h>
#include <malloc.h>
#include<stdio.h>
#include <stdlib.h>
#include<string.h>

// Input limit is 200 characters
#define MAX 202
#define PALINDROME 1
#define NOTPALINDROME 0
#define INVALID -1
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/// <summary>Function which checks if a given string is palindrome or not</summary>
int PalindromeChecker (char* phrase) {
   int i = 0, j = 0, length;
   char temp[MAX];
   length = (int)strlen (phrase);
   if (length > MAX - 2) {
      printf ("\nLimit exceeded");
      return INVALID;
   }
   // Eliminating special characters by moving the remaining character into a temporary array
   while (i < length) {
      if (isalnum (phrase[i]) != 0)
         temp[j++] = phrase[i];
      i++;
   }
   temp[j] = '\0';
   // Checking invalid text
   if (j == 0)
      return INVALID;
   i = 0;
   while (i < j / 2) {
      if (toupper (temp[i]) != toupper (temp[j - 1 - i]))
         return NOTPALINDROME;
      i++;
   }
   return PALINDROME;
}

/// <summary>Function which checks if the input number is palindrome or not</summary>
int NumberReverser (int number) {
   int rem, numTemp;
   long long int rev = 0;
   numTemp = number;
   while (numTemp != 0) {
      rem = numTemp % 10;
      rev = rev * 10 + rem;
      numTemp /= 10;
   }
   printf ("\nReversed: %lld", rev);
   return (number >= 0 && number == rev) ? PALINDROME : NOTPALINDROME;
}

/// <summary>Function to run test cases</summary>
void TestCases () {
   int* strOutputs = NULL, * numOutputs = NULL, strLength, numLength;
   char* strInputs[] = { "Was it a car or a cat I saw?", "I did, did I?", "Don't nod", "TRUMPF", "Metamation" };
   int numInputs[] = { 121,232,INT_MAX,INT_MIN,0 };
   int strExpected[] = { PALINDROME,PALINDROME,PALINDROME,NOTPALINDROME,NOTPALINDROME };
   int numExpected[] = { PALINDROME,PALINDROME,NOTPALINDROME,NOTPALINDROME,PALINDROME };
   strLength = sizeof (strInputs) / sizeof (strInputs[0]);
   numLength = sizeof (numInputs) / sizeof (numInputs[0]);
   do {
      strOutputs = (int*)malloc (strLength * sizeof (int));
   } while (strOutputs == NULL);
   for (int i = 0; i < strLength; i++) {
      printf ("\nInput: %s", strInputs[i]);
      strOutputs[i] = PalindromeChecker (strInputs[i]);
      printf ("\nExpected: %d\nOutput: %d", strExpected[i], strOutputs[i]);
      (strOutputs[i] == strExpected[i]) ? printf (ANSI_COLOR_GREEN"\nPassed\n"ANSI_COLOR_RESET) : printf (ANSI_COLOR_RED"\nFailed\n"ANSI_COLOR_RESET);
   }
   do {
      numOutputs = (int*)malloc (numLength * sizeof (int));
   } while (numOutputs == NULL);
   for (int i = 0; i < numLength; i++) {
      printf ("\nInput: %d", numInputs[i]);
      numOutputs[i] = NumberReverser (numInputs[i]);
      printf ("\nExpected: %d\nOutput: %d", numExpected[i], numOutputs[i]);
      (numOutputs[i] == numExpected[i]) ? printf (ANSI_COLOR_GREEN"\nPassed\n"ANSI_COLOR_RESET) : printf (ANSI_COLOR_RED"\nFailed\n"ANSI_COLOR_RESET);
   }
}

int main () {
   char ch = '\n', choice[3], * result, term;
   while (1) {
      printf ("Menu\n~~~~\n1. Palindrome Checker\n2. Number Reverser\n3. Run Test Cases\n\nEnter your choice: ");
      fgets (choice, sizeof (choice), stdin);
      result = strchr (choice, ch);
      if (result == NULL) {
         printf ("Invalid Choice!\n\n");
         // Draining the unassigned inputs from stdin
         for (; ; ) {
            term = fgetc (stdin);
            if (term == '\n')
               break;
         }
      } else {
         switch (choice[0]) {
            case '1': {
                  char phrase[MAX];
                  printf ("\nPalindrome Checker\n~~~~~~~~~~~~~~~~~~\nEnter a string: ");
                  fgets (phrase, MAX, stdin);
                  result = strchr (phrase, ch);
                  if (result == NULL) {
                     printf ("Input limit exceeded!\n");
                     for (; ; ) {
                        term = fgetc (stdin);
                        if (term == '\n')
                           break;
                     }
                  } else {
                     if (strlen (phrase) == MAX - 1)
                        phrase[MAX - 1] = '\0';
                     int pChecker = PalindromeChecker (phrase);
                     if (pChecker == PALINDROME)
                        printf ("Palindrome\n");
                     else if (pChecker == INVALID)
                        printf ("Enter a valid string!\n");
                     else
                        printf ("Not a palindrome!\n");
                  }
                  break;
               }
            case '2': {
                  char* endptr, number[13];
                  printf ("\nNumber Reverser\n~~~~~~~~~~~~~~~\nEnter a number: ");
                  fgets (number, 13, stdin);
                  result = strchr (number, ch);
                  if (result == NULL) {
                     printf ("Invalid Input!\n");
                     for (; ; ) {
                        term = fgetc (stdin);
                        if (term == '\n')
                           break;
                     }
                  } else {
                     errno = 0;
                     int num = strtol (number, &endptr, 10);
                     if (endptr == number || *endptr != '\n' || errno == ERANGE)
                        printf ("Invalid Input!\n");
                     else if (NumberReverser (num) == PALINDROME)
                        printf ("\nPalindrome\n");
                     else
                        printf ("\nNot a palindrome!\n");
                  }
                  break;
               }
            case '3': {
                  printf ("\nTest Cases\n~~~~~~~~~~");
                  TestCases ();
                  break;
               }
            default:
               printf ("Invalid Choice!\n");
         }
      }
      printf ("\n");
   }
   return 0;
}