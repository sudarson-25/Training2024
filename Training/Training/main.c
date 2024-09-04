// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// main.c
// Program to convert and display decimal value into binary and hexadecimal value.
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<malloc.h>
#include<math.h>

int* DecToBin (int dec, int* digits1) {
   int digitsCount = 0;
   int decReal = dec;
   if (dec < 0) dec *= -1;
   int decTemp = dec;
   //Counting the number of bits the binary representation will occupy
   digitsCount = (int)(ceil (log2 (dec)));
   // Representing binary in multiples of 8-bits accordingly
   if (digitsCount % 8 != 0) digitsCount += (8 - (digitsCount % 8));
   int* binRev = NULL;
   do {
      binRev = (int*)malloc (digitsCount * sizeof (int));
   } while (binRev == NULL);
   //Storing the remainders into binRev
   for (int i = 0; i < digitsCount; i++) {
      binRev[i] = decTemp % 2;
      decTemp /= 2;
   }
   if (decReal > 0) {
      int* bin;
      do {
         bin = (int*)malloc (digitsCount * sizeof (int));
      } while (bin == NULL);
      // Reverse storing the stored remainders
      for (int j = 0; j < digitsCount; j++)
         bin[j] = binRev[digitsCount - j - 1];
      *digits1 = digitsCount;
      return bin;
   } else { //Performing two's compliment
      int* binTwosComp = NULL;
      do {
         binTwosComp = (int*)malloc (digitsCount * sizeof (int));
      } while (binTwosComp == NULL);
      //Complimenting each element of the array
      for (int k = 0; k < digitsCount; k++)
         binTwosComp[k] = binRev[digitsCount - k - 1] == 0 ? 1 : 0;
      free (binRev);
      //Adding 1 to the the binary number (stored as individual digits)
      for (int k = digitsCount - 1; k >= 0; k--) {
         if (binTwosComp[k] == 0) {
            binTwosComp[k] = 1;
            break;
         } else binTwosComp[k] = 0;
      }
      *digits1 = digitsCount;
      return binTwosComp;
   }
}

char* DecToHex (int dec, int* digits2) {
   int digitsCount = 0;
   int decReal = dec;
   if (dec < 0) dec *= -1;
   int decTemp = dec;
   //Counting the number of bits the hex representation will occupy
   digitsCount = (int)ceil ((log (dec) / log (16)));
   // Representing hex in multiples of 8-bits accordingly
   if (digitsCount % 8 != 0) digitsCount += (8 - (digitsCount % 8));
   char* hexRev = NULL;
   do {
      hexRev = (char*)malloc (digitsCount * sizeof (char));
   } while (hexRev == NULL);
   //Storing the remainders into hexRev
   for (int i = 0; i < digitsCount; i++) {
      hexRev[i] = decTemp % 16 >= 10 ? (decTemp % 16) + 55 : (decTemp % 16) + 48;
      decTemp /= 16;
   }
   if (decReal > 0) {
      char* hex = NULL;
      do {
         hex = (char*)malloc (digitsCount + 1 * sizeof (char));
      } while (hex == NULL);
      int j;
      // Reverse storing the stored reaminders into hex
      for (j = 0; j < digitsCount; j++)
         hex[j] = hexRev[digitsCount - j - 1];
      hex[j] = '\0';
      free (hexRev);
      *digits2 = digitsCount;
      return hex;
   } else {
      //Decimal to binary
      int* bin = DecToBin (decReal, &digitsCount);
      int digit = 0, place = 0, icount = 0, count = digitsCount / 4;
      // Representing hex in multiples of 8-bits accordingly
      if (count % 8 != 0) count += (8 - (count % 8));
      char* hexNegRev = NULL;
      do {
         hexNegRev = (char*)malloc (count * sizeof (char));
      } while (hexNegRev == NULL);
      int ind = 0;
      //Converting binary to hex and storing into hexNegRev in reverse
      for (int i = digitsCount - 1; i >= 0; i--) {
         digit += bin[i] * (int)pow (2, place++);
         icount++;
         if (icount == 4) {
            place = 0, icount = 0;
            hexNegRev[ind++] = digit >= 10 ? digit + 55 : digit + 48;
            digit = 0;
         }
      }
      free (bin);
      while (ind < count)
         hexNegRev[ind++] = 'F';
      digitsCount = count;
      char* hexNeg = NULL;
      do {
         hexNeg = (char*)malloc (digitsCount + 1 * sizeof (char));
      } while (hexNeg == NULL);
      int k;
      // Storing hex values into hexNeg
      for (k = 0; k < digitsCount; k++)
         hexNeg[k] = hexNegRev[digitsCount - k - 1];
      hexNeg[k] = '\0';
      free (hexNegRev);
      *digits2 = digitsCount;
      return hexNeg;
   }
}

int main () {
   int dec, digits1, digits2;
   char term;
   while (1) {
      printf ("Input (Enter an integer): ");
      if (scanf_s ("%d%c", &dec, &term, 1) != 2 || term != '\n') {
         printf ("Enter a valid input!");
         //Draining the unassigned inputs from stdin
         for (; ; ) {
            term = fgetc (stdin);
            if (term == '\n') break;
         }
         printf ("\n\n");
      } else {
         if (dec == 0) {
            char converted[] = "00000000";
            printf ("Binary (8-bit): %s", converted);
            printf ("\nHEX (8-bit): %s", converted);
            printf ("\n\n");
         } else {
            int* bin = DecToBin (dec, &digits1);
            printf ("Binary (%d-bit): ", digits1);
            for (int i = 0; i < digits1; i++)
               printf ("%d", bin[i]);
            char* hex = DecToHex (dec, &digits2);
            printf ("\nHEX (%d-bit): ", digits2);
            printf ("%s", hex);
            free (bin);
            free (hex);
            printf ("\n\n");
         }
      }
   }
   return 0;
}