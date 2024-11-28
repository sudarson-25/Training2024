// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// change.c
// Program to perform and test arithmetic operations on complex numbers.
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<errno.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h> // USED

void OptimalChangeCalculator (int* coins, int rem, int* denominations) {
   for (int i = 0; i < 4; i++) {
      coins[i] = rem / denominations[i];
      rem %= denominations[i];
   }
}

static void Testcases (int* denominations) {
   int input[] = { 95,75,67,79 }, expected[][4] = { 9,1,0,0,7,1,0,0,6,1,1,0,7,1,2,0 }, output[4];
   printf ("\nTestcases\n~~~~~~~~~\n");
   for (int i = 0; i < sizeof (input) / sizeof (input[0]); i++) {
      OptimalChangeCalculator (output, input[i], denominations);
      int j;
      for (j = 0; j < 4; j++)
         if (expected[i][j] != output[j]) {
            printf ("Case %d: FAILED\n", i + 1);
            break;
         }
      if (j == 4) printf ("Case %d: PASSED\n", i + 1);
   }
}

/// <summary>Returns user inputs only if they are valid integers</summary>
static int GetValidInteger (char* prompt) {
   bool output;
   int num;
   do {
      char numberStr[4096];
      printf ("%s", prompt);
      fgets (numberStr, sizeof (numberStr), stdin);
      if (output = strchr (numberStr, '\n') != NULL) {
         errno = 0;
         char* endptr = NULL;
         num = strtol (numberStr, &endptr, 10);
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE;
      }
      if (!output || num < 0) printf ("Invalid Input\n");
   } while (!output || num < 0);
   return num;
}

int main () {
   int actual, paid, denominations[] = { 10,5,2,1 };
   actual = GetValidInteger ("Actual Amount: ");
   paid = GetValidInteger ("Cash paid: ");
   int change = paid - actual;
   if (change < 0) printf ("Cash paid is less than the actual amount");
   else {
      int coins[4];
      OptimalChangeCalculator (coins, change, denominations);
      for (int i = 0; i < 4; i++)
         printf ("No. of Rs.%d coins: %d\n", denominations[i], coins[i]);
   }
   Testcases (denominations);
   return 0;
}