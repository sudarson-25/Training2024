#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// complex.h
// Contains function signatures
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<stdbool.h>

typedef struct ComplexNumber {
   float Real, Img;
}Complex;

/// <summary>Adds two complex numbers</summary>
Complex OpAdd (Complex A, Complex B);

/// <summary>Subtracts one complex number from another</summary>
Complex OpSub (Complex A, Complex B);

/// <summary>Multiplies two complex numbers</summary>
Complex OpMul (Complex A, Complex B);

/// <summary>Computes the modulus of a complex number</summary>
double OpMod (Complex A);

/// <summary>Computes the conjugate of a complex number</summary>
Complex OpConj (Complex A);

/// <summary>Prints a complex number</summary>
void PrintComplex (Complex C);

/// <summary>Compares 2 complex numbers and returns true if they are equal</summary>
bool IsEqual (Complex C, Complex D);