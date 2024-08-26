#include "intlist.h"
#include <malloc.h>
#include<stdbool.h>

struct LinkedList* Create () {
   struct LinkedList* list = NULL;
   do {
      list = (struct LinkedList*)malloc (sizeof (struct LinkedList));
      if (list != NULL) {
         list->head = NULL;
         list->isDeleted = false;
         list->count = 0;
      }
   } while (list == NULL);
   return list;
}

struct Node* CreateNode (int data) {
   struct Node* newNode = NULL;
   do {
      newNode = (struct Node*)malloc (sizeof (struct Node));
      if (newNode != NULL) {
         newNode->data = data;
         newNode->next = NULL;
      }
   } while (newNode == NULL);
   return newNode;
}

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
      for (int i = 0; i < ind - 1; i++) {
         temp = temp->next;
      }
      prev = temp;
      temp = temp->next;
      prev->next = temp->next;
      free (temp);
      list->count--;
      return 0;
   } else // If given index is found, delete node
      return E_INVALID_INDEX;
}

int Remove (struct LinkedList* list, int data) {
   if (list->isDeleted == true)
      return E_LIST_DNE;
   if (list->head == NULL)
      return E_EMPTY_LIST;
   // Store head node
   struct Node* temp = list->head;
   struct Node* prev = NULL;
   // If head node itself holds the data to be deleted
   if (temp->data == data) {
      // Changed head
      list->head = temp->next;
      free (temp);
      list->count--;
      return 0;
   }
   // Search for the data to be deleted, keep track of the
   // previous node as we need to change 'prev->next'
   while (temp != NULL && temp->data != data) {
      prev = temp;
      temp = temp->next;
   }
   if (temp != NULL) {
      prev->next = temp->next;
      free (temp);
      list->count--;
      return 0;
   } else // If data was not present in linked list
      return E_INVALID_ELEMENT;
}

int Count (struct LinkedList* list) {
   if (list->isDeleted == true) return E_LIST_DNE;
   return list->count;
}

int Get (struct LinkedList* list, int ind, int* data) {
   if (list->isDeleted == true) {
      *data = 0;
      return E_LIST_DNE;
   }
   if (list->head == NULL) {
      *data = 0;
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
   *data = 0;
   return E_INVALID_INDEX;
}