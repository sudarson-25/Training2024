// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// testcomplex.c
// Program to perform arithmetic operations on complex numbers.
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include"complex.h"

/// <summary>Runs testcases for various arithmetic operations</summary>
static void TestCases () {
   Complex input[] = { 5,4,6,-5 }, expected[] = { 11,-1,-1,9,50,-1,5,-4 };
   double modExpected = 6.4031242374328485;
   Complex D = OpAdd (input[0], input[1]), E = OpSub (input[0], input[1]),
      F = OpMul (input[0], input[1]), G = OpConj (input[0]);
   D.real == expected[0].real && D.img == expected[0].img ? printf ("\nADD Passed") : printf ("\nADD Failed");
   E.real == expected[1].real && E.img == expected[1].img ? printf ("\nSUB Passed") : printf ("\nSUB Failed");
   F.real == expected[2].real && F.img == expected[2].img ? printf ("\nMUL Passed") : printf ("\nMUL Failed");
   //Testing CONJ and MOD with the first complex number
   G.real == expected[3].real && G.img == expected[3].img ? printf ("\nCONJ Passed") : printf ("\nCONJ Failed");
   OpMod (input[0]) == modExpected ? printf ("\nMOD Passed\n") : printf ("\nMOD Failed\n");
}

/// <summary>Prints a complex number</summary>
static void PrintComplex (Complex C) {
   C.img >= 0 ? printf ("%0.2f+%0.2fi\n", C.real, C.img) : printf ("%0.2f%0.2fi\n", C.real, C.img);
}

int main () {
   Complex A = { 0,0 }, B = { 0,0 };
   printf ("Enter the real part of the first number: ");
   scanf_s ("%f", &A.real);
   printf ("Enter the img part of the first number: ");
   scanf_s ("%f", &A.img);
   printf ("Enter the real part of the second number: ");
   scanf_s ("%f", &B.real);
   printf ("Enter the img part of the second number: ");
   scanf_s ("%f", &B.img);
   printf ("\nAddition: ");
   PrintComplex (OpAdd (A, B));
   printf ("\nSubtraction: ");
   PrintComplex (OpSub (A, B));
   printf ("\nMultiplication: ");
   PrintComplex (OpMul (A, B));
   printf ("\nModulus of A: %0.2lf\n", OpMod (A));
   printf ("\nConjugate of A: ");
   PrintComplex (OpConj (A));
   TestCases ();
   return 0;
}