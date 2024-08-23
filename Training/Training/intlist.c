#include "intlist.h"
#include <malloc.h>
#include<stdbool.h>

/// <summary>Returns pointer to a new LinkedList with head = NULL and isDeleted = false</summary>
/// <returns>LinkedList pointer</returns>
struct LinkedList* Create () {
   struct LinkedList* list = (struct LinkedList*)malloc (sizeof (struct LinkedList));
   if (list != NULL) {
      list->head = NULL;
      list->isDeleted = false;
      list->count = 0;
      return list;
   } else
      return E_INVALID_LIST;
}

/// <summary>
/// This function allocates space for a new Node structure and assigns values to its members
/// </summary>
/// <param name="data"></param>
/// <returns>Node pointer</returns>
struct Node* CreateNode (int data) {

   struct Node* newNode = (struct Node*)malloc (sizeof (struct Node));
   if (newNode != NULL) {
      newNode->data = data;
      newNode->next = NULL;
   }
   return newNode;
}

/// <summary>Deletes all the nodes</summary>
/// <param name="list"></param>
/// <returns>Error code (if any)</returns>
int Delete (struct LinkedList* list) {
   if (list->isDeleted == true)
      return E_LIST_DNE;

   if (list->head == NULL) {
      list->isDeleted = true;
      return 0;
   }

   struct Node* temp = NULL;

   while (list->head != NULL) {
      temp = list->head;
      list->head = (list->head)->next;
      free (temp);
   }
   list->isDeleted = true;
   return 0;
}

/// <summary>
/// The flag ensures whether the list exists.
/// Adds nodes to an existing list. 
/// </summary>
/// <param name="list"></param>
/// <param name="data"></param>
/// <returns>Error code (if any)</returns>
int Add (struct LinkedList* list, int data) {
   if (list->isDeleted == true)
      return E_LIST_DNE;

   struct Node* newNode = CreateNode (data);

   // in case this is the first node, make the newNode as
   // the head of the LinkedList
   if (list->head == NULL) {
      list->head = newNode;
      list->count++;
      return 0;
   }
   // Create a pointer to iterate till the last node
   struct Node* current = list->head;
   while (current->next != NULL)
      current = current->next;
   // make the next of the tail to the newNode
   current->next = newNode;
   list->count++;
   return 0;
}


/// <summary>
/// The flag ensures whether the list exists.
/// Inserts a node at the specified index with the specified value into the list
/// </summary>
/// <param name="list"></param>
/// <param name="ind"></param>
/// <param name="data"></param>
/// <returns>Error code (if any)</returns>
int Insert (struct LinkedList* list, int ind, int data) {

   if (list->isDeleted == true)
      return E_LIST_DNE;

   struct Node* newNode = CreateNode (data);

   // If inserting at the beginning
   if (ind == 0) {
      newNode->next = list->head;
      list->head = newNode;
      list->count++;
      return 0;
   }

   int count = Count (list);
   struct Node* current = list->head;
   if (current == NULL) {
      free (newNode);
      return E_INVALID_INDEX;
   }

   if (ind >= 0 && ind < count) {
      for (int i = 0; i < ind - 1; i++)
         current = current->next;

   } else { // If the position is out of bounds
      free (current);
      return E_INVALID_INDEX;
   }

   newNode->next = current->next;
   current->next = newNode;
   list->count++;
   return 0;
}


/// <summary>
/// The flag ensures whether the list exists.
/// Removes the node at a specified index from the list.
/// </summary>
/// <param name="list"></param>
/// <param name="ind"></param>
/// <returns>Error code (if any)</returns>
int RemoveAt (struct LinkedList* list, int ind) {

   if (list->isDeleted == true)
      return E_LIST_DNE;

   // Base case if linked list is empty
   if (list->head == NULL)
      return E_EMPTY_LIST;

   struct Node* temp = list->head;
   struct Node* prev = NULL;

   // Case 1: Head is to be deleted
   if (ind == 0) {
      list->head = temp->next;
      free (temp);
      list->count--;
      return 0;
   }

   // Case 2: Node to be deleted is in middle
   // Traverse till given position

   int count = Count (list);

   if (ind >= 0 && ind < count) {
      for (int i = 0; i < ind; i++) {
         prev = temp;
         temp = temp->next;
      }
      prev->next = temp->next;
      free (temp);
      list->count--;
      return 0;
   } else // If given index is found, delete node
      return E_INVALID_INDEX;
}


/// <summary>
/// The flag ensures whether the list exists.
/// Removes the Node with the specified data value from the list.
/// </summary>
/// <param name="list"></param>
/// <param name="data"></param>
/// <returns>Error code (if any)</returns>
int Remove (struct LinkedList* list, int data) {

   if (list->isDeleted == true)
      return E_LIST_DNE;

   // Store head node
   struct Node* temp = list->head;
   struct Node* prev = NULL;

   if (temp == NULL)
      return E_EMPTY_LIST;

   // If head node itself holds the key to be deleted
   if (temp != NULL && temp->data == data) {
      // Changed head
      list->head = temp->next;
      free (temp);
      list->count--;
      return 0;
   }

   // Search for the key to be deleted, keep track of the
   // previous node as we need to change 'prev->next'
   while (temp != NULL && temp->data != data) {
      prev = temp;
      temp = temp->next;
   }

   // If key was not present in linked list
   if (temp != NULL) {
      prev->next = temp->next;
      free (temp);
      list->count--;
      return 0;
   } else
      return E_INVALID_ELEMENT;

}


/// <summary>
/// The flag ensures whether the list exists.
/// Counts the number of nodes in the list.
/// </summary>
/// <param name="list"></param>
/// <returns>count/Error code (if any)</returns>
int Count (struct LinkedList* list) {

   if (list->isDeleted == true)
      return E_LIST_DNE;
   else
      return list->count;
}


/// <summary>
/// The flag ensures whether the list exists.
/// Stores the value at a specified index if such an index exists in a pointer.
/// </summary>
/// <param name="list"></param>
/// <param name="ind"></param>
/// <param name="data"></param>
/// <returns>Error code (if any)</returns>
int Get (struct LinkedList* list, int ind, int* data) {

   if (list->isDeleted == true) {
      *data = NULL;
      return E_LIST_DNE;
   }

   if (list->head == NULL) {
      *data = NULL;
      return E_EMPTY_LIST;
   }

   struct Node* current = list->head;

   // the index of the node we're currently looking at 
   int count = 0;
   while (current != NULL) {
      if (count == ind) {
         *data = current->data;
         return 0;
      }
      count++;
      current = current->next;
   }

   *data = NULL;
   return E_INVALID_INDEX;
}