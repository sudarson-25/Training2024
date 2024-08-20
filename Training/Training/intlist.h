#pragma once
#include<stdbool.h>

// errors
#define E_EMPTY_LIST -1
#define E_INVALID_INDEX -2
#define E_INVALID_ELEMENT -3
#define E_LIST_DNE -4

struct Node {
	int data;
	struct Node* next;
};

struct LinkedList {
	struct Node* head;
	bool isDeleted;  // bool variable to flag deleted lists
};

//Creates an empty linked list
struct LinkedList* Create ();

//Creates a node
struct Node* CreateNode (int data);

//Deletes the entire linked list
int Delete (struct LinkedList* list);

//Adds an element to the list
int Add (struct LinkedList* list, int data);

//Inserts an element at the specified index
int Insert (struct LinkedList* list, int ind, int data);

//Removes the element at the specified index
int RemoveAt (struct LinkedList* list, int ind);

//Removes the first occurance of the specified element from the list
int Remove (struct LinkedList* list, int data);

//Counts the number of elements in the list
int Count (struct LinkedList* list);

//Returns the element present at a specified index
int Get (struct LinkedList* list, int ind);