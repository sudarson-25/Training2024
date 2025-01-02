// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// training.c
// Program to display the chess board
// Sudarson S
// ------------------------------------------------------------------------------------------------
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <malloc.h>

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
      int refFilesize = filelength (fileno (rfp)) + 1,
         outFilesize = filelength (fileno (ofp)) + 1;
      wchar_t* refFileContent = (wchar_t*)malloc (refFilesize * sizeof (wchar_t)),
         * outFileContent = (wchar_t*)malloc (outFilesize * sizeof (wchar_t));
      fgetws (refFileContent, refFilesize, rfp);
      fgetws (outFileContent, outFilesize, ofp);
      wprintf (L"\nTestcase: ");
      if (refFilesize == 1 || outFilesize == 1) wprintf (L"File has no content!\n");
      else if (refFilesize != outFilesize) wprintf (L"Files are of different length\n");
      else {
         int j;
         for (j = 0; j < refFilesize - 1; j++) {
            if (refFileContent[j] != outFileContent[j]) {
               wprintf (ANSI_COLOR_RED L"FAILED\n" ANSI_COLOR_RESET);
               break;
            }
         }
         if (refFileContent[j] == outFileContent[j]) wprintf (ANSI_COLOR_GREEN L"PASSED\n" ANSI_COLOR_RESET);
         free (refFileContent);
         free (outFileContent);
      }
   }
   fclose (rfp);
   fclose (ofp);
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