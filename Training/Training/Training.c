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
         else {
            validChar++;
            i++;
            j--;
         }
   }
   return validChar != 0 ? PALINDROME : INVALID;
}

/// <summary>Function which checks if the input number is palindrome or not</summary>
int NumberReverser (int number, long long int* rev) {
   int rem, numTemp;
   if (number >= 0 && number <= 9) {
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
   while (getchar () != '\n');
}

/// <summary>Function to check if the given input is a phrase or a number</summary>
bool IsValidNum (char* phrase, int* num) {
   char* endptr;
   *num = strtol (phrase, &endptr, 10);
   if (endptr == phrase || *endptr != '\0' || errno == ERANGE || phrase[0] == ' ' || phrase[0] == '\t')
      return false;
   else
      return true;
}

/// <summary>Function to run test cases</summary>
void TestCases () {
   int Length, pChecker, num;
   long long int rev;
   char* Inputs[] = { "Was it a car or a cat I saw?", "I did, did I?", "Don't nod", "TRUMPF",
      "Metamation", "121", "232", "123454321", "123456789", "0", "!@#  $%", " " }, * Expected[] = { "Palindrome", "Palindrome",
      "Palindrome", "Not a Palindrome", "Not a Palindrome","Palindrome", "Palindrome",
      "Palindrome", "Not a Palindrome", "Palindrome", "Invalid", "Invalid" }, * output = NULL;
   Length = sizeof (Inputs) / sizeof (Inputs[0]);
   printf (ANSI_COLOR_YELLOW"\n-------------------------------------------------------------------"
           "--------------\n|------------Input-------------|-----Expected-----|------Output------"
           "|--Result--|"ANSI_COLOR_RESET);
   for (int i = 0; i < Length; i++) {
      rev = 0;
      if (IsValidNum (Inputs[i], &num))
         pChecker = NumberReverser (num, &rev);
      else
         pChecker = PalindromeChecker (Inputs[i]);
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
   int output, isNum = 1, num;
   fgets (phrase, MAX, stdin);
   result = strchr (phrase, '\n');
   if (result == NULL) {
      printf ("Enter a valid string!\n");
      BufferDrain ();
   } else {
      phrase[strlen (phrase) - 1] = '\0';
      if (IsValidNum (phrase, &num)) {
         long long int rev = 0;
         output = NumberReverser (num, &rev);
         Display (output, isNum, rev);
      } else {
         isNum = 0;
         long long int placeholder = 0;
         output = PalindromeChecker (phrase);
         Display (output, isNum, placeholder);
      }
   }
}

int main () {
   char ch = '\n', choice[3], * result = NULL;
   while (1) {
      printf ("Menu\n~~~~\n1. Palindrome Checker / Number Reverser\n2. Run Test Cases\n"
              "3. Exit\n\nEnter your choice: ");
      fgets (choice, sizeof (choice), stdin);
      result = strchr (choice, ch);
      if (result == NULL) {
         printf ("Invalid Choice!\n");
         BufferDrain ();
      } else {
         switch (choice[0]) {
            case '1': {
                  printf ("\nPalindrome Checker / Number Reverser\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                          "~~~~~");
                  printf ("\nInput: ");
                  UserInput ();
                  break;
               }
            case '2':
               printf ("\nTest Cases\n~~~~~~~~~~");
               TestCases ();
               break;
            case '3':
               return 0;
            default:
               printf ("Invalid Choice!\n");
         }
      }
      printf ("\n");
   }
}