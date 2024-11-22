// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Program.c
// Program to perform and test arithmetic operations on 2 complex numbers.
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<math.h>

typedef struct ComplexNumber {
   float real;
   float img;
}Complex;

static Complex OpAdd (Complex A, Complex B) {
   Complex C;
   C.real = A.real + B.real;
   C.img = A.img + B.img;
   return C;
}

static Complex OpSub (Complex A, Complex B) {
   Complex C;
   C.real = A.real - B.real;
   C.img = A.img - B.img;
   return C;
}

static Complex OpMul (Complex A, Complex B) {
   Complex C;
   C.real = A.real * B.real - A.img * B.img;
   C.img = A.real * B.img + A.img * B.real;
   return C;
}

static double OpMod (Complex A) {
   double mod = sqrt (pow (A.real, 2) + pow (A.img, 2));
   return mod;
}

static Complex OpConj (Complex A) {
   A.img = -A.img;
   return A;
}

static void TestCases () {
   Complex input[] = { 5,4,6,-5 }, expected[] = { 11,-1,-1,9,50,-1,5,-4 };
   double modExpected = 6.4031242374328485;

   Complex D = OpAdd (input[0], input[1]), E = OpSub (input[0], input[1]),
      F = OpMul (input[0], input[1]), G = OpConj (input[0]);
   D.real == expected[0].real && D.img == expected[0].img ? printf ("\nADD Passed") : printf ("\nADD Failed");
   E.real == expected[1].real && E.img == expected[1].img ? printf ("\nSUB Passed") : printf ("\nSUB Failed");
   F.real == expected[2].real && F.img == expected[2].img ? printf ("\nMUL Passed") : printf ("\nMUL Failed");
   //Checking CONJ and MOD with the first complex number
   G.real == expected[3].real && G.img == expected[3].img ? printf ("\nCONJ Passed") : printf ("\nCONJ Failed");
   OpMod (input[0]) == modExpected ? printf ("\nMOD Passed") : printf ("\nMOD Failed");
}

int main () {
   Complex A, B, C;
   double mod;
   printf ("Enter the real part of first number: ");
   scanf_s ("%f", &A.real);
   printf ("Enter the img part of first number: ");
   scanf_s ("%f", &A.img);
   printf ("Enter the real part of second number: ");
   scanf_s ("%f", &B.real);
   printf ("Enter the img part of first number: ");
   scanf_s ("%f", &B.img);
   C = OpAdd (A, B);
   C.img > 0 ? printf ("%0.2f+%0.2fi\n", C.real, C.img) : printf ("%0.2f%0.2fi\n", C.real, C.img);
   C = OpSub (A, B);
   C.img > 0 ? printf ("%0.2f+%0.2fi\n", C.real, C.img) : printf ("%0.2f%0.2fi\n", C.real, C.img);
   C = OpMul (A, B);
   C.img > 0 ? printf ("%0.2f+%0.2fi\n", C.real, C.img) : printf ("%0.2f%0.2fi\n", C.real, C.img);
   mod = OpMod (A);
   printf ("%0.2f\n", mod);
   C = OpConj (A);
   C.img > 0 ? printf ("%0.2f+%0.2fi\n", C.real, C.img) : printf ("%0.2f%0.2fi\n", C.real, C.img);
   TestCases ();
   return 0;
}