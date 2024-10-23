// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// training.c
// Selection sort and binary search functions are defined
// Sudarson S
// ------------------------------------------------------------------------------------------------
#include"training.h"

int BinarySearch (int* arr, int arrSize, int key) {
   int low = 0, high = arrSize - 1, idx = -1;
   while (low <= high) {
      int mid = low + (high - low) / 2;
      // Checks if key is present at mid and is it's first occurrence
      arr[mid] == key ? idx = mid, high = mid - 1 : arr[mid] < key ? low = mid + 1 : (high = mid - 1);
   }
   return idx;
}

void SelectionSort (int* arr, int n) {
   for (int i = 0; i < n - 1; i++) {
      int minIdx = i;
      // Iterate through the unsorted portion to find the actual minimum
      for (int j = i + 1; j < n; j++)
         if (arr[j] < arr[minIdx]) minIdx = j; // Update minInd if a smaller element is found
      // If a new minimum is found, swap it with the element at index i
      if (minIdx != i) {
         int temp = arr[i];
         arr[i] = arr[minIdx];
         arr[minIdx] = temp;
      }
   }
}