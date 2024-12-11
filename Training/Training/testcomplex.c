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
   Complex input[] = { {5,4},{6,-5},{0,0},{-987,76}, {1,2},{9,-80},{56274,2435},{17,173} };
   for (int i = 0; i < 7; i += 2) {
      Complex D = OpAdd (input[i], input[i + 1]), E = OpSub (input[i], input[i + 1]),
         F = OpMul (input[i], input[i + 1]), G = OpConj (input[i]),
         H = { input[i].Real + input[i + 1].Real, input[i].Img + input[i + 1].Img },
         I = { input[i].Real - input[i + 1].Real, input[i].Img - input[i + 1].Img },
         J = { input[i].Real * input[i + 1].Real - input[i].Img * input[i + 1].Img,
         input[i].Real * input[i + 1].Img + input[i].Img * input[i + 1].Real },
         K = { input[i].Real, -input[i].Img };
      printf (Compare (D, H) ? "\nADD Passed" : "\nADD Failed");
      printf (Compare (E, I) ? "\nSUB Passed" : "\nSUB Failed");
      printf (Compare (F, J) ? "\nMUL Passed" : "\nMUL Failed");
      ////Testing CONJ and MOD with the first complex number
      printf (Compare (G, K) ? "\nCONJ Passed" : "\nCONJ Failed");
      printf (OpMod (input[i]) == sqrt (input[i].Real * input[i].Real + input[i].Img * input[i].Img) ?
         "\nMOD Passed\n" : "\nMOD Failed\n");
   }
}

int main () {
   TestCases ();
   return 0;
}