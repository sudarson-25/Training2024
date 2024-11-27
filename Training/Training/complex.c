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

Complex OpAdd (Complex A, Complex B) {
   Complex C = { A.real + B.real, A.img + B.img };
   return C;
}

Complex OpSub (Complex A, Complex B) {
   Complex C = { A.real - B.real, A.img - B.img };
   return C;
}

Complex OpMul (Complex A, Complex B) {
   Complex C = { A.real * B.real - A.img * B.img, A.real * B.img + A.img * B.real };
   return C;
}

double OpMod (Complex A) {
   double mod = sqrt (A.real * A.real + A.img * A.img);
   return mod;
}

Complex OpConj (Complex A) {
   A.img = -A.img;
   return A;
}