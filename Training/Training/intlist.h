#pragma once
#include<stdbool.h>

// errors
/// <summary>Returned when list is empty</summary>
#define E_EMPTY_LIST -1
/// <summary>Returned when index is invalid</summary>
#define E_INVALID_INDEX -2
/// <summary>Returned when element is invalid</summary>
#define E_INVALID_ELEMENT -3
/// <summary>Returned when list does not exist</summary>
#define E_LIST_DNE -4
/// <summary>Returned when list is not created</summary>
#define E_INVALID_LIST -5
/// <summary>Returned when node is not created</summary>
#define E_INVALID_NODE -6

struct Node {
   int data;
   struct Node* next;
};

struct LinkedList {
   struct Node* head;
   bool isDeleted;  // bool variable to flag deleted lists
   int count;
};

/// <summary>Creates an empty linked list</summary>
struct LinkedList* Create ();

/// <summary>Creates a node</summary>
struct Node* CreateNode (int data);

/// <summary>Deletes the entire linked list</summary>
int Delete (struct LinkedList* list);

/// <summary>Adds an element to the list</summary>
int Add (struct LinkedList* list, int data);

/// <summary>Inserts an element at the specified index</summary>
int Insert (struct LinkedList* list, int ind, int data);

/// <summary>Removes the element at the specified index</summary>
int RemoveAt (struct LinkedList* list, int ind);

/// <summary>Removes the first occurance of the specified element from the list</summary>
int Remove (struct LinkedList* list, int data);

/// <summary>Counts the number of elements in the list</summary>
int Count (struct LinkedList* list);

/// <summary>Returns the element present at a specified index</summary>
int Get (struct LinkedList* list, int ind, int* data);