#pragma once

// errors
#define EMPTY_LIST -1
#define INVALID_INDEX -2
#define INALID_ELEMENT -3
#define LIST_DOE -4

struct Node* Create ();
struct Node* CreateNode (int data);
int Delete (struct Node** head);
int Add (struct Node** head, int data);
int Insert (struct Node** head, int ind, int data);
int RemoveAt (struct Node** head, int ind);
int Remove (struct Node** head, int ele);
int Count (struct Node* head);
int Get (struct Node* head, int ind);