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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
   int i = 0, validChar = 0, length = (int)strlen (phrase), j = length - 1;
   if (length > MAX - 2)
      return INVALID;
   // Checking if valid characters from the beginning and the end match with each other
   while (i <= j) {
      if (isalnum (phrase[i]) == 0)
         i++;
      else if (isalnum (phrase[j]) == 0)
         j--;
      else
         if (toupper (phrase[i]) != toupper (phrase[j]))
            return NOTPALINDROME;
         else
            validChar++, i++, j--;
   }
   return validChar != 0 ? PALINDROME : INVALID;
}

/// <summary>Function which checks if the input number is palindrome or not</summary>
long long int NumberReverser (int number) {
   int numTemp;
   long long int rev = 0;
   if (number >= 0 && number <= 9) {
      rev = number;
      return rev;
   }
   numTemp = number;
   while (numTemp != 0) {
      rev = rev * 10 + numTemp % 10;
      numTemp /= 10;
   }
   return rev;
}

/// <summary>Function to drain the unassigned inputs from stdin</summary>
void BufferDrain () {
   while (getchar () != '\n');
}

/// <summary>Function to check if the given input is a phrase or a number</summary>
bool IsValidNum (char* phrase, int* num) {
   errno = 0;
   char* endptr = NULL;
   *num = strtol (phrase, &endptr, 10);
   return endptr == phrase || *endptr != '\0' || errno == ERANGE || phrase[0] == ' ' || phrase[0] == '\t' ?
      false : true;
}

/// <summary>Function to run test cases</summary>
void TestCases () {
   int Length;
   char* Inputs[] = { "Was it a car or a cat I saw?", "I did, did I?", "Don't nod", "TRUMPF",
      "Metamation", "121", "232", "123454321", "123456789", "0", "!@#  $%", " ", "-878" }, * Expected[] = {
      "Palindrome", "Palindrome", "Palindrome", "Not a Palindrome", "Not a Palindrome","Palindrome",
      "Palindrome", "Palindrome", "Not a Palindrome", "Palindrome", "Invalid", "Invalid", "Not a Palindrome" },
      * output = NULL;
   Length = sizeof (Inputs) / sizeof (Inputs[0]);
   printf (ANSI_COLOR_YELLOW"\n-------------------------------------------------------------------"
           "--------------\n|------------Input-------------|-----Expected-----|------Output------"
           "|--Result--|"ANSI_COLOR_RESET);
   for (int i = 0; i < Length; i++) {
      int num, pChecker;
      long long int rev = 0;
      pChecker = IsValidNum (Inputs[i], &num) ?
         ((NumberReverser (num) == num && num >= 0) ? PALINDROME : NOTPALINDROME) :
         PalindromeChecker (Inputs[i]);
      output = pChecker == PALINDROME ? "Palindrome" : pChecker == NOTPALINDROME ?
         "Not a Palindrome" : "Invalid";
      printf ("\n  %-31s%-19s%-20s%s", Inputs[i], Expected[i], output,
              strcmp (output, Expected[i]) == 0 ? ANSI_COLOR_GREEN"Passed"ANSI_COLOR_RESET :
              ANSI_COLOR_RED"Failed"ANSI_COLOR_RESET);
   }
   printf (ANSI_COLOR_YELLOW"\n-------------------------------------------------------------------"
           "--------------\n"ANSI_COLOR_RESET);
}

/// <summary>Function to display the appropriate message and/or the reversed number</summary>
void Display (int output, int isNum, long long int rev) {
   isNum == 0 ? printf (output == PALINDROME ? "Palindrome\n" : output == INVALID ?
                        "Enter a valid string!\n" : "Not a palindrome!\n") :
      output == PALINDROME ? printf ("\nReversed: %lld\nPalindrome\n", rev) :
      printf ("\nReversed: %lld\nNot a palindrome!\n", rev);
}

/// <summary>Function to accept input from the user</summary>
void UserInput () {
   char phrase[MAX], * result = NULL;
   fgets (phrase, MAX, stdin);
   result = strchr (phrase, '\n');
   if (result == NULL) {
      printf ("Enter a valid string!\n");
      BufferDrain ();
   } else {
      int output, isNum = 1, num;
      long long int rev = 0;
      phrase[strlen (phrase) - 1] = '\0';
      IsValidNum (phrase, &num) ? (output = (rev = NumberReverser (num)) == num && num >= 0 ?
                                   PALINDROME : NOTPALINDROME) : (isNum = 0, output =
                                                                  PalindromeChecker (phrase));
      Display (output, isNum, rev);
   }
}

int main () {
   while (1) {
      char choice[3], * result = NULL;
      printf ("Menu\n~~~~\n1. Palindrome Checker / Number Reverser\n2. Run Test Cases\n"
              "3. Exit\n\nEnter your choice: ");
      fgets (choice, sizeof (choice), stdin);
      result = strchr (choice, '\n');
      if (result == NULL) {
         printf ("Invalid Choice!\n");
         BufferDrain ();
      } else
         switch (choice[0]) {
            case '1':
               printf ("\nPalindrome Checker / Number Reverser\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                       "~~~~~");
               printf ("\nInput: ");
               UserInput ();
               break;
            case '2':
               printf ("\nTest Cases\n~~~~~~~~~~");
               TestCases ();
               break;
            case '3':
               return 0;
            default:
               printf ("Invalid Choice!\n");
         }
      printf ("\n");
   }
}