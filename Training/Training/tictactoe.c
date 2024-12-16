// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// Program.c
// Program for Tic-Tac-Toe
// ------------------------------------------------------------------------------------------------

#include<errno.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h> // USED

#define WIN -1
#define LOSE -2
#define DRAW -3
#define PLAY -4

/// <summary>Returns user inputs only if they are valid integers</summary>
static int GetValidInteger (char* prompt) {
   bool output;
   int validInt;
   do {
      char numberStr[4096];
      printf ("%s", prompt);
      fgets (numberStr, sizeof (numberStr), stdin);
      if (output = strchr (numberStr, '\n') != NULL) {
         errno = 0;
         char* endptr = NULL;
         validInt = strtol (numberStr, &endptr, 10);
         output = endptr != numberStr && *endptr == '\n' && errno != ERANGE && validInt > 0;
      }
   } while (!output);
   return validInt;
}

/// <summary>Prints the box after each player's input </summary>
static void PrintBox (int* board) {
   for (int i = 0; i < 3; i++) {
      printf (" %d | %d | %d \n", board[i * 3], board[i * 3 + 1], board[i * 3 + 2]);
      if (i < 2) printf ("---+---+---\n");
   }
}

/// <summary>Returns true if the given player won</summary>
bool CheckWin (int* box, int player) {
   int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
   };
   for (int j = 0; j < 8; j++)
      if (box[winConditions[j][0]] == player &&
         box[winConditions[j][1]] == player &&
         box[winConditions[j][2]] == player) return true;
   return false;
}

/// <summary>Returns the game status</summary>
int CheckStatus (int* box, int player1, int player2) {
   int i;
   if (CheckWin (box, player1)) return WIN;
   else if (CheckWin (box, player2)) return LOSE;
   for (i = 0; i < 9 && box[i] != 0; i++);
   if (i == 9) return DRAW;
   return PLAY;
}

/// <summary>Prompts the game's next move and accepts user input</summary>
static void NextTurn (char* prompt, int* box, int player) {
   int boxNo;
   printf ("%s", prompt);
   do
      boxNo = GetValidInteger ("Enter box no: ");
   while (boxNo < 1 || boxNo > 9 || box[boxNo - 1] != 0);
   box[boxNo - 1] = player;
   PrintBox (box);
}

int main () {
   int player1, player2, statusChecker, box[9] = { 0 };
   do
      player1 = GetValidInteger ("Choose your symbol (1 or 2): ");
   while (player1 != 1 && player1 != 2);
   player1 == 1 ? player2 = 2 : (player2 = 1);
   do {
      NextTurn ("\nYour Turn:\n", box, player1);
      statusChecker = CheckStatus (box, player1, player2);
      if (statusChecker == PLAY) {
         NextTurn ("\nOpponent's Turn:\n", box, player2);
         statusChecker = CheckStatus (box, player1, player2);
      }
   } while (statusChecker == PLAY);
   if (statusChecker == WIN) printf ("\nYOU WIN\n");
   else if (statusChecker == LOSE) printf ("\nYOU LOSE\n");
   else printf ("\nDRAW\n");
   return 0;
}