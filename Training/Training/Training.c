// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Training.c
// Program to check for armstrong number.
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

static int GetValidInteger (char* prompt) {
   bool output;
   int validInt;
   do {
      char numberStr[4096];
      printf ("%s", prompt);
      fgets (numberStr, sizeof (numberStr), stdin);
      if (output = strchr (numberStr, '\n') != NULL) {
         errno = 0;
         char* endptr = NULL;
         validInt = strtol (numberStr, &endptr, 10);
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && validInt > 0;
      }
   } while (!output);
   return validInt;
}

void ArmstrongChecker (int num) {
   int digits = 0, num1, num2;
   double arm = 0;
   num1 = num2 = num;
   while (num1 > 0) {
      num1 /= 10;
      digits++;
   }
   while (num2 > 0) {
      int rem = num2 % 10;
      num2 /= 10;
      arm += pow (rem, digits);
   }
   if (arm == num)
      printf ("\nArmstrong Number!\n");
   else
      printf ("\nNot an armstrong number\n");
}

int main () {
   int num = GetValidInteger ("Enter a number: ");
   ArmstrongChecker (num);
   return 0;
}