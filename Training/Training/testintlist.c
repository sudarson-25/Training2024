// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// testintlist.c
// Program for testing functions related to linked lists.
// ------------------------------------------------------------------------------------------------

#include <stdio.h>
#include "intlist.h"

int main () {

	//Create
	printf ("Create\n");
	struct Node* head = Create ();
	printf ("Case1\n");
	printf ("Expected: 0000000000000000\n");
	printf ("Output:   %p\n\n", head);

	//Add
	//Adding to empty list
	printf ("Add\n");
	printf ("Case2\n");
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", Add (&head, 10));

	//Adding to a deleted list
	printf ("Case3\n");
	Delete (&head);
	printf ("Expected: -4\n");
	printf ("Output: %d\n\n", Add (&head, 20));


	//Delete
	//Deleting a list
	printf ("Delete\n");
	printf ("Case4\n");
	head = Create ();
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", Delete (&head));

	//Deleting a deleted list
	printf ("Case5\n");
	printf ("Expected: -4\n");
	printf ("Output: %d\n\n", Delete (&head));


	//Insert
	//Inserting into a deleted list
	printf ("Insert\n");
	printf ("Case6\n");
	printf ("Expected: -4\n");
	printf ("Output: %d\n\n", Insert (&head, 3, 20));

	//Inserting into an invalid index
	head = Create ();
	printf ("Case7\n");
	printf ("Expected: -2\n");
	printf ("Output: %d\n\n", Insert (&head, 3, 20));

	//Inserting into a valid index
	printf ("Case8\n");
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", Insert (&head, 0, 20));


	//RemoveAt
	//When the list doesn't exist
	printf ("RemoveAt\n");
	Delete (&head);
	printf ("Case9\n");
	printf ("Expected: -4\n");
	printf ("Output: %d\n\n", RemoveAt (&head, 0));

	//When the list is empty
	head = Create ();
	printf ("Case10\n");
	printf ("Expected: -1\n");
	printf ("Output: %d\n\n", RemoveAt (&head, 4));

	//Invalid Index
	Add (&head, 20);
	printf ("Case11\n");
	printf ("Expected: -2\n");
	printf ("Output: %d\n\n", RemoveAt (&head, 4));

	//When index is valid
	printf ("Case12\n");
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", RemoveAt (&head, 0));


	//Remove
	// Removing when list does not exist
	printf ("Remove\n");
	Delete (&head);
	printf ("Case13\n");
	printf ("Expected: -4\n");
	printf ("Output: %d\n\n", Remove (&head, 20));

	//Removing from an empty list
	head = Create ();
	printf ("Case14\n");
	printf ("Expected: -1\n");
	printf ("Output: %d\n\n", Remove (&head, 20));

	//Removing an invalid element
	Add (&head, 20);
	Add (&head, 20);
	Add (&head, 20);
	Add (&head, 20);
	printf ("Case15\n");
	printf ("Expected: -3\n");
	printf ("Output: %d\n\n", Remove (&head, 30));

	//Removing a valid element
	printf ("Case15\n");
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", Remove (&head, 20));


	//Count
	//When list exists (Count now is 3)
	printf ("Count\n");
	printf ("Case16\n");
	printf ("Expected: 3\n");
	printf ("Output: %d\n\n", Count (head));

	//When list doesn't exists
	Delete (&head);
	printf ("Case17\n");
	printf ("Expected: -4\n");
	printf ("Output: %d\n\n", Count (head));


	//Get
	// When list doesn't exist
	printf ("Get\n");
	printf ("Case18\n");
	printf ("Expected: -4\n");
	printf ("Output: %d\n\n", Get (head, 3));

	//When list is empty
	head = Create ();
	printf ("Case19\n");
	printf ("Expected: -1\n");
	printf ("Output: %d\n\n", Get (head, 0));

	//When index is invalid
	Add (&head, 20);
	printf ("Case20\n");
	printf ("Expected: -2\n");
	printf ("Output: %d\n\n", Get (head, 1));

	//When index is valid (Value at index 0 is 20)
	printf ("Case20\n");
	printf ("Expected: 20\n");
	printf ("Output: %d\n\n", Get (head, 0));

	return 0;
}