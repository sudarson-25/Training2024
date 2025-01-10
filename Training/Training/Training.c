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
#include<math.h>
#include<string.h>

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

bool ArmstrongChecker (int num) {
   int digits = 0, tempVar = num, tempVar2 = num;
   double arm = 0;
   for (; tempVar > 0; digits++) tempVar /= 10;
   for (; tempVar2 > 0; tempVar2 /= 10) arm += pow (tempVar2 % 10, digits);
   return arm == num;
}

int main () {
   int num = GetValidInteger ("Enter a number: ");
   if (ArmstrongChecker (num))
      printf ("\nArmstrong Number!\n");
   else
      printf ("\nNot an armstrong number\n");
   return 0;
}