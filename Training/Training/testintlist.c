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
	struct LinkedList* list = Create ();
	printf ("Case1\n");
	printf ("Expected: 0000000000000000\n");
	printf ("Output:   %p\n\n", list->head);

	//Add
	//Adding to an empty list
	printf ("Add\n");
	printf ("Case2\n");
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", Add (list, 10));

	//Adding to a deleted list
	printf ("Case3\n");
	Delete (list);
	printf ("Expected: %d\n", E_LIST_DNE);
	printf ("Output: %d\n\n", Add (list, 20));


	//Delete
	//Deleting a list
	printf ("Delete\n");
	printf ("Case4\n");
	list = Create ();
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", Delete (list));

	//Deleting a deleted list
	printf ("Case5\n");
	printf ("Expected: %d\n", E_LIST_DNE);
	printf ("Output: %d\n\n", Delete (list));


	//Insert
	//Inserting into a deleted list
	printf ("Insert\n");
	printf ("Case6\n");
	printf ("Expected: %d\n", E_LIST_DNE);
	printf ("Output: %d\n\n", Insert (list, 3, 20));

	//Inserting into an invalid index
	list = Create ();
	printf ("Case7\n");
	printf ("Expected: %d\n", E_INVALID_INDEX);
	printf ("Output: %d\n\n", Insert (list, 3, 20));

	//Inserting into a valid index
	printf ("Case8\n");
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", Insert (list, 0, 20));


	//RemoveAt
	//When the list doesn't exist
	printf ("RemoveAt\n");
	Delete (list);
	printf ("Case9\n");
	printf ("Expected: %d\n", E_LIST_DNE);
	printf ("Output: %d\n\n", RemoveAt (list, 0));

	//When the list is empty
	list = Create ();
	printf ("Case10\n");
	printf ("Expected: %d\n", E_EMPTY_LIST);
	printf ("Output: %d\n\n", RemoveAt (list, 4));

	//Invalid Index
	Add (list, 20);
	printf ("Case11\n");
	printf ("Expected: %d\n", E_INVALID_INDEX);
	printf ("Output: %d\n\n", RemoveAt (list, 4));

	//When index is valid
	printf ("Case12\n");
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", RemoveAt (list, 0));


	//Remove
	// Removing when list does not exist
	printf ("Remove\n");
	Delete (list);
	printf ("Case13\n");
	printf ("Expected: %d\n", E_LIST_DNE);
	printf ("Output: %d\n\n", Remove (list, 20));

	//Removing from an empty list
	list = Create ();
	printf ("Case14\n");
	printf ("Expected: %d\n", E_EMPTY_LIST);
	printf ("Output: %d\n\n", Remove (list, 20));

	//Removing an invalid element
	Add (list, 20);
	Add (list, 20);
	Add (list, 20);
	Add (list, 20);
	printf ("Case15\n");
	printf ("Expected: %d\n", E_INVALID_ELEMENT);
	printf ("Output: %d\n\n", Remove (list, 30));

	//Removing a valid element
	printf ("Case15\n");
	printf ("Expected: 0\n");
	printf ("Output: %d\n\n", Remove (list, 20));


	//Count
	//When list exists (Count now is 3)
	printf ("Count\n");
	printf ("Case16\n");
	printf ("Expected: 3\n");
	printf ("Output: %d\n\n", Count (list));

	//When list doesn't exists
	Delete (list);
	printf ("Case17\n");
	printf ("Expected: %d\n", E_LIST_DNE);
	printf ("Output: %d\n\n", Count (list));


	//Get
	// When list doesn't exist
	printf ("Get\n");
	printf ("Case18\n");
	printf ("Expected: %d\n", E_LIST_DNE);
	printf ("Output: %d\n\n", Get (list, 3));

	//When list is empty
	list = Create ();
	printf ("Case19\n");
	printf ("Expected: %d\n", E_EMPTY_LIST);
	printf ("Output: %d\n\n", Get (list, 0));

	//When index is invalid
	Add (list, 20);
	printf ("Case20\n");
	printf ("Expected: %d\n", E_INVALID_INDEX);
	printf ("Output: %d\n\n", Get (list, 1));

	//When index is valid (Value at index 0 is 20)
	printf ("Case20\n");
	printf ("Expected: 20\n");
	printf ("Output: %d\n\n", Get (list, 0));

	return 0;
}
