// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// test.c
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

static void PrintWrite (const wchar_t* const character, FILE* fp) {
   wprintf (L"%s", character);
   fputws (character, fp);
}

static void PrintBox (const wchar_t* const symbol1, const wchar_t* const symbol2, const wchar_t*
   const symbol3, FILE* fp) {
   PrintWrite (symbol1, fp);
   for (int i = 1; i <= 7; i++) {
      for (int i = 1; i <= 4; i++) PrintWrite (L"━", fp);
      PrintWrite (symbol2, fp);
   }
   for (int i = 1; i <= 4; i++) PrintWrite (L"━", fp);
   PrintWrite (symbol3, fp);
}

static void TestCases (char* outputFile, char* referenceFile) {
   FILE* ofp = fopen (outputFile, "r"), * rfp = fopen (referenceFile, "r");
   if (ofp == NULL) wprintf (L"Could not open output file\n");
   else if (rfp == NULL) wprintf (L"Could not open reference file\n");
   else {
      wint_t outChar = fgetwc (ofp), refChar = fgetwc (rfp);
      int matchFlag = 0, charFlag = 0;
      wprintf (L"\n Testcase: ");
      while (outChar != WEOF || refChar != WEOF)
         if (outChar != refChar) {
            wprintf (ANSI_COLOR_RED L"FAILED\n" ANSI_COLOR_RESET);
            break;
         } else {
            outChar = fgetwc (ofp);
            refChar = fgetwc (rfp);
         }
      if (outChar == WEOF && refChar == WEOF) wprintf (ANSI_COLOR_GREEN L"PASSED\n" ANSI_COLOR_RESET);
      fclose (ofp);
      fclose (rfp);
   }
}

int main () {
   int a = _setmode (_fileno (stdout), _O_U16TEXT);
   char* outputFile = "unicode_output.txt", * referenceFile = "reference.txt";
   FILE* fp = fopen (outputFile, "w, ccs=UTF-8");
   if (fp == NULL) wprintf (L"Could not open output file for writing\n");
   else {
      const wchar_t* const pieces[2][8] = { L"♜", L"♞", L"♝", L"♛", L"♚", L"♝", L"♞", L"♜",
         L"♖", L"♘", L"♗", L"♕", L"♔", L"♗", L"♘", L"♖" };
      PrintBox (L"┏", L"┳", L"┓", fp);
      PrintWrite (L"\n", fp);
      for (int i = 1; i <= 8; i++) {
         switch (i) {
            case 1: for (int j = 0; j < 8; j++) {
               wprintf (L"┃  %s ", pieces[0][j]);
               fputws (L"┃  ", fp);
               fputws (pieces[0][j], fp);
               fputws (L" ", fp);
            }break;
            case 2: for (int j = 0; j < 8; j++) PrintWrite (L"┃  ♟", fp);
               break;
            case 7:for (int j = 0; j < 8; j++) PrintWrite (L"┃  ♙ ", fp);
               break;
            case 8:for (int j = 0; j < 8; j++) {
               wprintf (L"┃  %s ", pieces[1][j]);
               fputws (L"┃  ", fp);
               fputws (pieces[1][j], fp);
               fputws (L" ", fp);
            }break;
            default:for (int j = 1; j <= 8; j++)
               PrintWrite (L"┃    ", fp);
         }
         PrintWrite (L"┃\n", fp);
         if (i != 8) {
            PrintBox (L"┣", L"╋", L"┫", fp);
            PrintWrite (L"\n", fp);
         }
      }
      PrintBox (L"┗", L"┻", L"┛", fp);
      fclose (fp);
   }
   TestCases (outputFile, referenceFile);
   return 0;
}