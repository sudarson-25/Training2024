// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// complex.c
// Functions performing arithmetic operations on complex numbers are defined.
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include"complex.h"
#include<math.h>
#include<stdbool.h>
#include<stdio.h>

Complex OpAdd (Complex A, Complex B) {
   Complex C = { A.Real + B.Real, A.Img + B.Img };
   return C;
}

Complex OpSub (Complex A, Complex B) {
   Complex C = { A.Real - B.Real, A.Img - B.Img };
   return C;
}

Complex OpMul (Complex A, Complex B) {
   Complex C = { A.Real * B.Real - A.Img * B.Img, A.Real * B.Img + A.Img * B.Real };
   return C;
}

double OpMod (Complex A) {
   double mod = sqrt (A.Real * A.Real + A.Img * A.Img);
   return mod;
}

Complex OpConj (Complex A) {
   A.Img = -A.Img;
   return A;
}

void PrintComplex (Complex C) {
   C.Img >= 0 ? printf ("%0.2f +%0.2fi\n", C.Real, C.Img) : printf ("%0.2f %0.2fi\n", C.Real, C.Img);
}

bool Compare (Complex C, Complex D) {
   return C.Real == D.Real && C.Img == D.Img;
}