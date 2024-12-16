// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// testcomplex.c
// Program to perform arithmetic operations on complex numbers.
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<math.h>
#include"complex.h"

/// <summary>Runs testcases for various arithmetic operations</summary>
static void TestCases () {
   Complex input[] = { {5,4},{6,-5},{0,0},{-987.24f,76},{1,2},{9,-80},{56274.23f,2435},{17.45f,173} };
   printf ("TestCases\n~~~~~~~~~\n");
   for (int i = 0; i < sizeof (input) / sizeof (input[0]); i += 2) {
      Complex H = { input[i].Real + input[i + 1].Real, input[i].Img + input[i + 1].Img },
         I = { input[i].Real - input[i + 1].Real, input[i].Img - input[i + 1].Img },
         J = { input[i].Real * input[i + 1].Real - input[i].Img * input[i + 1].Img,
         input[i].Real * input[i + 1].Img + input[i].Img * input[i + 1].Real },
         K = { input[i].Real, -input[i].Img };
      if (!IsEqual (OpAdd (input[i], input[i + 1]), H)) {
         printf ("ADD Failed:\n");
         PrintComplex (input[i]);
         PrintComplex (input[i + 1]);
         return;
      }
      if (!IsEqual (OpSub (input[i], input[i + 1]), I)) {
         printf ("SUB Failed:\n");
         PrintComplex (input[i]);
         PrintComplex (input[i + 1]);
         return;
      }
      if (!IsEqual (OpMul (input[i], input[i + 1]), J)) {
         printf ("MUL Failed:\n");
         PrintComplex (input[i]);
         PrintComplex (input[i + 1]);
         return;
      }
      ////Testing CONJ and MOD with the first complex number
      if (!IsEqual (OpConj (input[i]), K)) {
         printf ("CONJ Failed:\n");
         PrintComplex (input[i]);
         return;
      }
      if (OpMod (input[i]) != sqrt (input[i].Real * input[i].Real + input[i].Img * input[i].Img)) {
         printf ("MOD Failed:\n");
         PrintComplex (input[i]);
         return;
      }
   }
   printf ("Passed\n");
}

int main () {
   TestCases ();
   return 0;
}