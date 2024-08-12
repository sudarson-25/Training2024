#include "intlist.h"
#include <malloc.h>
#include<stdbool.h>

// bool variable to flag deleted lists
bool isDeleted = false;

struct Node {
	int data;
	struct Node* next; //we can create pointers to incomplete types
};


/// <summary>
/// This function declares and initialises a Node pointer to NULL and returns it.
/// </summary>
/// <returns>Node Pointer</returns>
struct Node* Create () {
	struct Node* head = NULL;
	isDeleted = false;
	return head;
}


/// <summary>
/// This function allocates space for a new Node and assigns values to its members
/// </summary>
/// <param name="data"></param>
/// <returns>Node Pointer</returns>
struct Node* CreateNode (int data) {

	struct Node* newNode = (struct Node*)malloc (sizeof (struct Node));
	if (newNode != NULL) {
		newNode->data = data;
		newNode->next = NULL;
	}
	return newNode;
}


/// <summary>
/// The flag ensures whether the list exists.
/// The function then checks if the head pointer points to a list(empty or with nodes).
/// If it points to a node, the node's address is temporarily stored in a pointer. The head pointer is modified to point to 
/// the next node and the previous node is freed.
/// </summary>
/// <param name="head"></param>
/// <returns>Error code (if any)</returns>
int Delete (struct Node** head) {

	if (isDeleted == true) {
		return LIST_DOE;
	}

	if (*head == NULL) {
		isDeleted = true;
		return 0;
	}

	struct Node* temp = NULL;

	while (*head != NULL) {
		temp = *head;
		*head = (*head)->next;
		free (temp);
	}
	isDeleted = true;
	return 0;
}


/// <summary>
/// The flag ensures whether the list exists.
/// Adds Nodes to an existing list. 
/// </summary>
/// <param name="head"></param>
/// <param name="data"></param>
/// <returns>Error code (if any)</returns>
int Add (struct Node** head, int data) {

	if (isDeleted == true) {
		return LIST_DOE;
	}

	struct Node* newNode = CreateNode (data);

	// in case this is the first node make the newNode as
	// the head of the LinkedList
	if (*head == NULL) {
		*head = newNode;
		return 0;
	}
	// Create a pointer to iterate till the last node
	struct Node* current = *head;
	while (current->next != NULL) {
		current = current->next;
	}
	// make the next of the tail to the new Node
	current->next = newNode;
	return 0;
}


/// <summary>
/// The flag ensures whether the list exists.
/// Inserts a Node at the specified index with the specified value into the list
/// </summary>
/// <param name="head"></param>
/// <param name="ind"></param>
/// <param name="data"></param>
/// <returns>Error code (if any)</returns>
int Insert (struct Node** head, int ind, int data) {

	if (isDeleted == true) {
		return LIST_DOE;
	}

	//if (*head == NULL)
	//	return EMPTY_LIST;

	struct Node* newNode = CreateNode (data);

	// If inserting at the beginning
	if (ind == 0) {
		newNode->next = *head;
		*head = newNode;
		return 0;
	}

	struct Node* current = *head;
	for (int i = 0; i < ind - 1 && current != NULL; ++i) {
		current = current->next;
	}

	// If the position is out of bounds
	if (current == NULL || ind < 0) {
		free (newNode);
		return INVALID_INDEX;
	}

	newNode->next = current->next;
	current->next = newNode;
	return 0;
}


/// <summary>
/// The flag ensures whether the list exists.
/// Removes the Node at a specified index from the list.
/// </summary>
/// <param name="head"></param>
/// <param name="ind"></param>
/// <returns>Error code (if any)</returns>
int RemoveAt (struct Node** head, int ind) {

	if (isDeleted == true) {
		return LIST_DOE;
	}

	struct Node* temp = *head;
	struct Node* prev = NULL;

	// Base case if linked list is empty
	if (temp == NULL)
		return EMPTY_LIST;

	// Case 1: Head is to be deleted
	if (ind == 0) {
		*head = temp->next;
		free (temp);
		return 0;
	}

	// Case 2: Node to be deleted is in middle
	// Traverse till given position
	for (int i = 0; temp != NULL && i < ind; i++) {
		prev = temp;
		temp = temp->next;
	}

	// If given index is found, delete node
	if (temp != NULL && prev != NULL) {
		prev->next = temp->next;
		free (temp);
		return 0;
	} else {
		return INVALID_INDEX;
	}
}


/// <summary>
/// The flag ensures whether the list exists.
/// Removes the Node with the specified data value from the list.
/// </summary>
/// <param name="head"></param>
/// <param name="ele"></param>
/// <returns>Error code (if any)</returns>
int Remove (struct Node** head, int ele) {

	if (isDeleted == true) {
		return LIST_DOE;
	}

	// Store head node
	struct Node* temp = *head;
	struct Node* prev = NULL;

	if (temp == NULL)
		return EMPTY_LIST;

	// If head node itself holds the key to be deleted
	if (temp != NULL && temp->data == ele) {

		// Changed head
		*head = temp->next;
		free (temp);
		return 0;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && temp->data != ele) {
		prev = temp;
		temp = temp->next;
	}

	// If key was not present in linked list
	if (temp != NULL) {
		prev->next = temp->next;
		free (temp);
		return 0;
	} else
		return INALID_ELEMENT;

}


/// <summary>
/// The flag ensures whether the list exists.
/// Counts the number of nodes in the list.
/// </summary>
/// <param name="head"></param>
/// <returns>count/Error code (if any)</returns>
int Count (struct Node* head) {

	if (isDeleted == true) {
		return LIST_DOE;
	}

	int count = 0;
	while (head != NULL) {
		count++;
		head = head->next;
	}
	return count;
}


/// <summary>
/// The flag ensures whether the list exists.
/// Returns the value at a specified index if such index exists.
/// </summary>
/// <param name="head"></param>
/// <param name="ind"></param>
/// <returns>data</returns>
int Get (struct Node* head, int ind) {

	if (isDeleted == true) {
		return LIST_DOE;
	}

	struct Node* current = head;

	if (current == NULL)
		return EMPTY_LIST;

	// the index of the 
	// node we're currently 
	// looking at 
	int count = 0;
	while (current != NULL) {
		if (count == ind)
			return (current->data);
		count++;
		current = current->next;
	}

	return INVALID_INDEX;
}