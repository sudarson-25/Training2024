// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// main.c
// Program to convert and display decimal value into binary and hexadecimal value.
// Sudarson S
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<malloc.h>
#include<math.h>
#include<limits.h>
#include<string.h>

#define BYTESIZE 8
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

/// <summary>
/// Function that counts the number of bits the binary/hex representation will occupy
/// and alters the count to the succeeding multiple of 8.
/// </summary>
int DigitsCount (int dec, int div) {
   int digitsCount;
   if (dec == 0)
      digitsCount = BYTESIZE;
   else {
      digitsCount = (int)((log ((double)dec) / log (div)) + 1);
      if (digitsCount % BYTESIZE != 0) digitsCount += (BYTESIZE - (digitsCount % BYTESIZE));
   }
   return digitsCount;
}

int* DecToBin (int dec, int* digits) {
   int digitsCount = 0, decReal = dec, decTemp, * bin = NULL;
   if (dec < 0) dec *= -1;
   decTemp = dec;
   digitsCount = DigitsCount (dec, 2);
   *digits = digitsCount;
   do {
      bin = (int*)malloc (digitsCount * sizeof (int));
   } while (bin == NULL);
   //Storing the remainders into binRev
   for (int i = digitsCount - 1; i >= 0; i--) {
      bin[i] = decTemp % 2;
      decTemp /= 2;
   }
   if (decReal >= 0) {
      return bin;
   } else { //Performing two's compliment
      int* binTwosComp = NULL;
      do {
         binTwosComp = (int*)malloc (digitsCount * sizeof (int));
      } while (binTwosComp == NULL);
      //Complimenting each element of the array
      for (int k = 0; k < digitsCount; k++)
         binTwosComp[k] = bin[k] == 0 ? 1 : 0;
      //Adding 1 to the the binary number (stored as individual digits)
      for (int k = digitsCount - 1; k >= 0; k--) {
         binTwosComp[k] = !binTwosComp[k];
         if (binTwosComp[k] == 1)
            break;
      }
      return binTwosComp;
   }
}

char* DecToHex (int dec, int* digits) {
   int digitsCount = 0, decReal = dec, decTemp;
   char* hex = NULL;
   if (dec < 0) dec *= -1;
   decTemp = dec;
   digitsCount = DigitsCount (dec, 16);
   *digits = digitsCount;
   do {
      hex = (char*)malloc (digitsCount + 1 * sizeof (char));
   } while (hex == NULL);
   if (decReal >= 0) {
      //Storing the remainders into hexRev
      for (int i = digitsCount - 1; i >= 0; i--) {
         hex[i] = decTemp % 16 >= 10 ? (decTemp % 16) + 55 : (decTemp % 16) + 48;
         decTemp /= 16;
      }
      hex[digitsCount] = '\0';
      return hex;
   } else {
      int digit = 0, place = 0, icount = 0, count, countTemp, bindigits;
      count = countTemp = digitsCount;
      //Decimal to binary
      int* bin = DecToBin (decReal, &bindigits);
      char* hexNeg = NULL;
      do {
         hexNeg = (char*)malloc (count + 1 * sizeof (char));
      } while (hexNeg == NULL);
      //Converting binary to hex and storing into hexNeg
      for (int i = bindigits - 1; i >= 0; i--) {
         digit += bin[i] * (int)pow (2, place++);
         icount++;
         if (icount == 4) {
            place = 0, icount = 0;
            hexNeg[count - 1] = digit >= 10 ? digit + 55 : digit + 48;
            count--;
            digit = 0;
         }
      }
      free (bin);
      count -= 1;
      while (count >= 0)
         hexNeg[count--] = 'F';
      hexNeg[countTemp] = '\0';
      return hexNeg;
   }
}

void TestCases (int* userinputs, int length, char* binexpected[], char* hexexpected[]) {
   int digits, flag;
   char temp;
   printf ("Decimal to Binary\n");
   printf ("~~~~~~~~~~~~~~~~~\n");
   for (int i = 0; i < length; i++) {
      printf (ANSI_COLOR_YELLOW"Case %d"ANSI_COLOR_RESET"\n", i + 1);
      printf ("Input: %d\n", userinputs[i]);
      int* bin = DecToBin (userinputs[i], &digits);
      flag = 0;
      for (int j = 0; j < digits; j++) {
         temp = bin[j] + 48;
         if (temp == binexpected[i][j])
            flag++;
      }
      if (flag == digits)
         printf (ANSI_COLOR_GREEN"Passed"ANSI_COLOR_RESET"\n\n");
      else
         printf (ANSI_COLOR_RED"Failed"ANSI_COLOR_RESET"\n\n");
   }
   printf ("Decimal to Hex\n");
   printf ("~~~~~~~~~~~~~~\n");
   for (int i = 0; i < length; i++) {
      printf (ANSI_COLOR_YELLOW"Case %d"ANSI_COLOR_RESET"\n", i + 1);
      printf ("Input: %d\n", userinputs[i]);
      char* hex = DecToHex (userinputs[i], &digits);
      if (strcmp (hex, hexexpected[i]) == 0)
         printf (ANSI_COLOR_GREEN"Passed"ANSI_COLOR_RESET"\n\n");
      else
         printf (ANSI_COLOR_RED"Failed"ANSI_COLOR_RESET"\n\n");
   }
}

int main () {
   int dec, digits1, digits2, length;
   char term;
   int userinputs[] = { 0,INT_MAX,-4321,1234,5678 };
   length = sizeof (userinputs) / sizeof (userinputs[0]);
   char* binexpected[] = { "00000000", "01111111111111111111111111111111", "1110111100011111", "0000010011010010", "0001011000101110" };
   char* hexexpected[] = { "00000000","7FFFFFFF","FFFFEF1F", "000004D2", "0000162E" };
   TestCases (userinputs, length, binexpected, hexexpected);
   printf ("Data Convertor\n");
   printf ("~~~~~~~~~~~~~~\n");
   while (1) {
      printf ("Input (Enter an integer): ");
      if (scanf_s ("%d%c", &dec, &term, 1) != 2 || term != '\n') {
         printf ("Enter a valid input!\n\n");
         //Draining the unassigned inputs from stdin
         for (; ; ) {
            term = fgetc (stdin);
            if (term == '\n') break;
         }
      } else if (dec < INT_MIN || dec > INT_MAX)
         printf ("Input exceeds integer range\n\n");
      else {
         int* bin = DecToBin (dec, &digits1);
         printf ("Binary (%d-bit): ", digits1);
         for (int i = 0; i < digits1; i++)
            printf ("%d", bin[i]);
         char* hex = DecToHex (dec, &digits2);
         printf ("\nHEX (%d-bit): %s\n\n", digits2, hex);
         free (bin);
         free (hex);
         return 0;
      }
   }
}