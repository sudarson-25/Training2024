// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// training.c
// Program to display the chess board
// Sudarson S
// ------------------------------------------------------------------------------------------------
#include <corecrt.h>
#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

static void PrintWrite (wchar_t* character, FILE* fp) {
   wprintf (L"%s", character);
   fputws (character, fp);
}

static void TestCases (char* outputFile, char* referenceFile) {
   FILE* ofp = fopen (outputFile, "r"), * rfp = fopen (referenceFile, "r");
   if (ofp == NULL) wprintf (L"Could not open output file\n");
   else if (rfp == NULL) wprintf (L"Could not open reference file\n");
   else {
      wint_t outChar = fgetwc (ofp), refChar = fgetwc (rfp);
      wprintf (L"\nTestcase: ");
      while (outChar != WEOF || refChar != WEOF)
         if (outChar != refChar) {
            wprintf (ANSI_COLOR_RED L"FAILED\n" ANSI_COLOR_RESET);
            break;
         } else {
            outChar = fgetwc (ofp);
            refChar = fgetwc (rfp);
         }
      wprintf (ANSI_COLOR_GREEN L"PASSED\n" ANSI_COLOR_RESET);
      fclose (ofp);
      fclose (rfp);
   }
}

int main () {
   int a = _setmode (_fileno (stdout), _O_U16TEXT);
   char* outputFile = "C:\\etc\\unicode_output.txt", * referenceFile = "reference.txt";
   FILE* fp = fopen (outputFile, "w, ccs=UTF-8");
   if (fp == NULL) wprintf (L"Could not open output file for writing\n");
   else {
      wchar_t* pieces[2][8] = { L"♜", L"♞", L"♝", L"♛", L"♚", L"♝", L"♞", L"♜",
         L"♖", L"♘", L"♗", L"♕", L"♔", L"♗", L"♘", L"♖" };
      PrintWrite (L"┏━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┳━━━━┓\n", fp);
      for (int i = 1; i <= 8; i++) {
         if (i == 1 || i == 8) {
            int k = i == 1 ? 0 : 1;
            for (int j = 0; j < 8; j++) {
               wprintf (L"┃ %s  ", pieces[k][j]);
               fputws (L"┃ ", fp);
               fputws (pieces[k][j], fp);
               fputws (L"  ", fp);
            }
         } else if (i == 2 || i == 7) {
            wchar_t* piece = i == 2 ? L"┃ ♟  " : L"┃ ♙  ";
            for (int j = 0; j < 8; j++)
               PrintWrite (piece, fp);
         } else
            for (int j = 1; j <= 8; j++)
               PrintWrite (L"┃    ", fp);
      PrintWrite (L"┃\n", fp);
      if (i != 8)
         PrintWrite (L"┣━━━━╋━━━━╋━━━━╋━━━━╋━━━━╋━━━━╋━━━━╋━━━━┫\n", fp);
   }
   PrintWrite (L"┗━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┻━━━━┛", fp);
   fclose (fp);
}
TestCases (outputFile, referenceFile);
return 0;
}