// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to check for palindrome of a string or an integer
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Input limit is 200 characters
#define MAX 202
#define PALINDROME 1
#define NOTPALINDROME 0
#define INVALID -1
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/// <summary>Function which checks if a given string is palindrome or not</summary>
int PalindromeChecker (char* phrase) {
   int i = 0, j, length, validChar = 0;
   length = (int)strlen (phrase);
   j = length - 1;
   if (length > MAX - 2)
      return INVALID;
   // Checking if valid characters from the beginning and the end match with each other
   while (i <= j) {
      if (isalnum (phrase[i]) == 0)
         i++;
      else if (isalnum (phrase[j]) == 0)
         j--;
      else
         if (isalnum (phrase[i]) != 0 && isalnum (phrase[j]) != 0) {
            if (toupper (phrase[i]) != toupper (phrase[j]))
               return NOTPALINDROME;
            else {
               validChar++;
               i++;
               j--;
            }
         }
   }
   return validChar != 0 ? PALINDROME : INVALID;
}

/// <summary>Function which checks if the input number is palindrome or not</summary>
int NumberReverser (int number, long long int* rev) {
   int rem, numTemp;
   if (number >= -9 && number <= 9) {
      *rev = number;
      return PALINDROME;
   }
   numTemp = number;
   while (numTemp != 0) {
      rem = numTemp % 10;
      *rev = *rev * 10 + rem;
      numTemp /= 10;
   }
   return number >= 0 && number == *rev ? PALINDROME : NOTPALINDROME;
}

/// <summary>Function to drain the unassigned inputs from stdin</summary>
void BufferDrain () {
   char term;
   for (; ; ) {
      term = fgetc (stdin);
      if (term == '\n')
         break;
   }
}

/// <summary>Function to run test cases</summary>
void TestCases () {
   int strLength, numLength, output,
      numInputs[] = { 121,232,INT_MAX,INT_MIN,0 },
      strExpected[] = { PALINDROME,PALINDROME,PALINDROME,NOTPALINDROME,NOTPALINDROME },
      numExpected[] = { PALINDROME,PALINDROME,NOTPALINDROME,NOTPALINDROME,PALINDROME };
   long long int rev;
   char* strInputs[] = { "Was it a car or a cat I saw?", "I did, did I?", "Don't nod", "TRUMPF",
      "Metamation" };
   strLength = sizeof (strInputs) / sizeof (strInputs[0]);
   numLength = sizeof (numInputs) / sizeof (numInputs[0]);
   printf (ANSI_COLOR_YELLOW"\n-------------------------------------------------------------------"
           "--------------\n|------------Input-------------|-----Expected-----|------Output------"
           "|--Result--|"ANSI_COLOR_RESET);
   for (int i = 0; i < strLength; i++) {
      output = PalindromeChecker (strInputs[i]);
      printf ("\n  %-31s%-19s%-20s%s", strInputs[i],
              strExpected[i] == PALINDROME ? "Palindrome" : strExpected[i] == NOTPALINDROME ?
              "Not a Palindrome" : "Invalid",
              output == PALINDROME ? "Palindrome" : output == NOTPALINDROME ?
              "Not a Palindrome" : "Invalid",
              output == strExpected[i] ? ANSI_COLOR_GREEN"Passed"ANSI_COLOR_RESET :
              ANSI_COLOR_RED"Failed"ANSI_COLOR_RESET);
   }
   printf (ANSI_COLOR_YELLOW"\n-------------------------------------------------------------------"
           "--------------\n----------------------------------------------------------------------"
           "-----------\n|-----Input-----|---Reversed---|-----Expected-----|------Output------"
           "|--Result--|"ANSI_COLOR_RESET);
   for (int i = 0; i < numLength; i++) {
      rev = 0;
      output = NumberReverser (numInputs[i], &rev);
      printf ("\n  %-16d%-15lld%-19s%-20s%s", numInputs[i], rev,
              numExpected[i] == PALINDROME ? "Palindrome" : "Not a Palindrome",
              output == PALINDROME ? "Palindrome" : "Not a Palindrome",
              output == numExpected[i] ? ANSI_COLOR_GREEN"Passed"ANSI_COLOR_RESET :
              ANSI_COLOR_RED"Failed"ANSI_COLOR_RESET);
   }
   printf (ANSI_COLOR_YELLOW"\n-------------------------------------------------------------------"
           "--------------\n"ANSI_COLOR_RESET);
}

int main () {
   char ch = '\n', choice[3], * result = NULL;
   while (1) {
      printf ("Menu\n~~~~\n1. Palindrome Checker\n2. Number Reverser\n3. Run Test Cases\n"
              "4. Exit\n\nEnter your choice: ");
      fgets (choice, sizeof (choice), stdin);
      result = strchr (choice, ch);
      if (result == NULL) {
         printf ("Invalid Choice!\n");
         BufferDrain ();
      } else {
         switch (choice[0]) {
            case '1': {
                  char phrase[MAX];
                  printf ("\nPalindrome Checker\n~~~~~~~~~~~~~~~~~~\nEnter a string: ");
                  fgets (phrase, MAX, stdin);
                  result = strchr (phrase, ch);
                  if (result == NULL) {
                     printf ("Enter a valid string!\n");
                     BufferDrain ();
                  } else {
                     phrase[strlen (phrase) - 1] = '\0';
                     int pChecker = PalindromeChecker (phrase);
                     printf (pChecker == PALINDROME ? "Palindrome\n" : pChecker == INVALID ?
                             "Enter a valid string!\n" : "Not a palindrome!\n");
                  }
                  break;
               }
            case '2': {
                  char* endptr, number[13];
                  long long int rev = 0;
                  printf ("\nNumber Reverser\n~~~~~~~~~~~~~~~\nEnter a number: ");
                  fgets (number, sizeof (number), stdin);
                  result = strchr (number, ch);
                  if (result == NULL) {
                     printf ("Invalid Input!\n");
                     BufferDrain ();
                  } else {
                     errno = 0;
                     int num = strtol (number, &endptr, 10);
                     endptr == number || *endptr != '\n' || errno == ERANGE || number[0] == ' ' ||
                        number[0] == '\t' ?
                        printf ("Invalid Input!\n") : NumberReverser (num, &rev) == PALINDROME ?
                        printf ("\nReversed: %lld\nPalindrome\n", rev) :
                        printf ("\nReversed: %lld\nNot a palindrome!\n", rev);
                  }
                  break;
               }
            case '3':
               printf ("\nTest Cases\n~~~~~~~~~~");
               TestCases ();
               break;
            case '4':
               return 0;
            default:
               printf ("Invalid Choice!\n");
         }
      }
      printf ("\n");
   }
}