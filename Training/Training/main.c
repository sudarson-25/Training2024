#include<stdio.h>
#include<malloc.h>
#include<math.h>

int mCount;

//Function for counting the number of digits
int count (int dec, int div) {
   int c = 0;
   if (dec == 0)
      return 8;
   while (dec > 0) {
      dec /= div;
      c++;
   }
   return c;
}

int* DecToBin (int dec) {
   mCount = 0;
   int dec2 = dec;
   if (dec < 0)
      dec *= -1;
   int dec1 = dec;
   //Counting the number of digits in binary representation
   mCount = count (dec, 2);
   // Representing binary in multiples of 8-bits accordingly
   if (mCount % 8 != 0)
      mCount += (8 - (mCount % 8));
   int* binRev = NULL;
   do {
      binRev = (int*)malloc (mCount * sizeof (int));
   } while (binRev == NULL);
   //Storing the remainders into binRev
   for (int i = 0; i < mCount; i++) {
      binRev[i] = dec1 % 2;
      dec1 /= 2;
   }
   if (dec2 >= 0) {
      int* bin;
      do {
         bin = (int*)malloc (mCount * sizeof (int));
      } while (bin == NULL);
      // Reverse storing the stored remainders
      for (int j = 0; j < mCount; j++)
         bin[j] = binRev[mCount - j - 1];
      return bin;
   } else { //Performing two's compliment
      int* binTwosComp = NULL;
      do {
         binTwosComp = (int*)malloc (mCount * sizeof (int));
      } while (binTwosComp == NULL);
      //Complimenting each element of the array
      for (int k = 0; k < mCount; k++) {
         if (binRev[mCount - k - 1] == 0)
            binTwosComp[k] = 1;
         else
            binTwosComp[k] = 0;
      }
      free (binRev);
      //Adding 1 to the the binary number (stored as individual digits)
      for (int k = mCount - 1; k >= 0; k--) {
         if (binTwosComp[k] == 0) {
            binTwosComp[k] = 1;
            break;
         } else
            binTwosComp[k] = 0;
      }
      return binTwosComp;
   }
}

char* DecToHex (int dec) {
   mCount = 0;
   int dec2 = dec;
   if (dec < 0)
      dec *= -1;
   int dec1 = dec;
   //Counting the number of digits in hex representation
   mCount = count (dec, 16);
   // Representing hex in multiples of 8-bits accordingly
   if (mCount % 8 != 0)
      mCount += (8 - (mCount % 8));
   char* hexRev = NULL;
   do {
      hexRev = (char*)malloc (mCount * sizeof (char));
   } while (hexRev == NULL);
   //Storing the remainders into hexRev
   for (int i = 0; i < mCount; i++) {
      if (dec1 % 16 >= 10)
         hexRev[i] = (dec1 % 16) + 55;
      else
         hexRev[i] = (dec1 % 16) + 48;
      dec1 /= 16;
   }
   if (dec2 >= 0) {
      char* hex = NULL;
      do {
         hex = (char*)malloc (mCount + 1 * sizeof (char));
      } while (hex == NULL);
      int j;
      // Reverse storing the stored reaminders into hex
      for (j = 0; j < mCount; j++)
         hex[j] = hexRev[mCount - j - 1];
      hex[j] = '\0';
      free (hexRev);
      return hex;
   } else {
      //Decimal to binary
      int* bin = DecToBin (dec2);
      int digit = 0, place = 0, icount = 0, count = mCount / 4;
      // Representing hex in multiples of 8-bits accordingly
      if (count % 8 != 0)
         count += (8 - (count % 8));
      char* hexNegRev = NULL;
      do {
         hexNegRev = (char*)malloc (count * sizeof (char));
      } while (hexNegRev == NULL);
      int ind = 0;
      //Converting binary to hex and storing into hexNegRev in reverse
      for (int i = mCount - 1; i >= 0; i--) {
         digit += bin[i] * pow (2, place);
         place++;
         icount++;
         if (icount == 4) {
            place = 0;
            icount = 0;
            if (digit >= 10)
               hexNegRev[ind] = digit + 55;
            else
               hexNegRev[ind] = digit + 48;
            ind++;
            digit = 0;
         }
      }
      free (bin);
      while (ind < count) {
         hexNegRev[ind] = 'F';
         ind++;
      }
      mCount = count;
      char* hexNeg = NULL;
      do {
         hexNeg = (char*)malloc (mCount + 1 * sizeof (char));
      } while (hexNeg == NULL);
      int k;
      // Storing hex values into hexNeg
      for (k = 0; k < mCount; k++)
         hexNeg[k] = hexNegRev[mCount - k - 1];
      hexNeg[k] = '\0';
      free (hexNegRev);
      return hexNeg;
   }
}

int main () {
   int dec;
   char term;
   while (1) {
      printf ("Input (Enter an integer): ");
      if (scanf_s ("%d%c", &dec, &term, 1) != 2 || term != '\n') {
         printf ("Enter a valid input!");
         //Draining the inputs from stdin
         for (;;) {
            term = fgetc (stdin);
            if (term == '\n')
               break;
         }
         printf ("\n\n");
      } else {
         int* bin = DecToBin (dec);
         printf ("Binary (%d-bit): ", mCount);
         for (int i = 0; i < mCount; i++)
            printf ("%d", bin[i]);
         char* hex = DecToHex (dec);
         printf ("\nHEX (%d-bit): ", mCount);
         for (int i = 0; i < mCount; i++)
            printf ("%c", hex[i]);
         free (bin);
         free (hex);
         printf ("\n\n");
      }
   }
   return 0;
}