// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Program.c
// Program for Tic-Tac-Toe
// ------------------------------------------------------------------------------------------------

#include<stdio.h>
#define WIN -1
#define LOSE -2
#define CONTINUE -3

static int Check (int* box, int symbol, int opponent) {
   if ((box[0] == box[1] && box[0] == box[2] && box[0] == symbol) ||
      (box[3] == box[4] && box[3] == box[5] && box[3] == symbol) ||
      (box[6] == box[7] && box[6] == box[8] && box[6] == symbol) ||
      (box[0] == box[3] && box[0] == box[6] && box[0] == symbol) ||
      (box[1] == box[4] && box[1] == box[7] && box[1] == symbol) ||
      (box[2] == box[5] && box[2] == box[8] && box[2] == symbol) ||
      (box[0] == box[4] && box[0] == box[8] && box[0] == symbol) ||
      (box[2] == box[4] && box[2] == box[6] && box[2] == symbol)) {
      printf ("\nWIN");
      return WIN;
   } else if ((box[0] == box[1] && box[0] == box[2] && box[0] == opponent) ||
      (box[3] == box[4] && box[3] == box[5] && box[3] == opponent) ||
      (box[6] == box[7] && box[6] == box[8] && box[6] == opponent) ||
      (box[0] == box[3] && box[0] == box[6] && box[0] == opponent) ||
      (box[1] == box[4] && box[1] == box[7] && box[1] == opponent) ||
      (box[2] == box[5] && box[2] == box[8] && box[2] == opponent) ||
      (box[0] == box[4] && box[0] == box[8] && box[0] == opponent) ||
      (box[2] == box[4] && box[2] == box[6] && box[2] == opponent)) {
      printf ("\nLOSE");
      return LOSE;
   } else
      return CONTINUE;
}

int main () {
   int boxNo, symbol, opponent, flag = -3;
   int box[9] = { 0 };
   do {
      printf ("Choose your symbol (1 or 2): ");
      scanf_s ("%d", &symbol);
   } while (symbol != 1 && symbol != 2);
   symbol == 1 ? opponent = 2 : (opponent = 1);

   while (flag == -3) {
      printf ("\nYour Turn:\n");
      do {
         printf ("Enter box no: ");
         scanf_s ("%d", &boxNo);
      } while (boxNo < 1 || boxNo>9 || box[boxNo - 1] != 0);
      box[boxNo - 1] = symbol;
      printf ("\nOpponent's Turn:\n");
      do {
         printf ("Enter box no: ");
         scanf_s ("%d", &boxNo);
      } while (boxNo < 1 || boxNo>9 || box[boxNo - 1] != 0);
      box[boxNo - 1] = opponent;
      int i;
      for (i = 0; i < 9; i++)
         if (box[i] == 0)
            break;
      if (i == 9)
         printf ("\nDRAW");
      else
         flag = Check (box, symbol, opponent);
   }
   return 0;
}