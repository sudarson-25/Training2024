// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Program.c
// Program to find the number of coins of each denomination required.
// ------------------------------------------------------------------------------------------------

#include<stdio.h>

int main () {
   int paid, actual, rem, change;
   printf ("Cash paid: ");
   scanf_s ("%d", &paid);
   printf ("Actual Amount: ");
   scanf_s ("%d", &actual);
   change = paid - actual;
   printf ("No. of Rs.10 coins: %d\n", change / 10);
   rem = change % 10;
   printf ("No. of Rs.5 coins: %d\n", rem / 5);
   rem %= 5;
   printf ("No. of Rs.2 coins: %d\n", rem / 2);
   rem %= 2;
   printf ("No. of Re.1 coins: %d\n", rem / 1);
   return 0;
}