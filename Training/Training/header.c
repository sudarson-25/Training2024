#include "header.h"

void SelectionSort (int* arr, int n) {
   for (int i = 0; i < n - 1; i++) {
      int minIdx = i;
      // Iterate through the unsorted portion to find the actual minimum
      for (int j = i + 1; j < n; j++)
         if (arr[j] < arr[minIdx])
            // Update minInd if a smaller element is found
            minIdx = j;
      // If a new minimum is found, swap it with the element at index i
      if (minIdx != i) {
         arr[i] += arr[minIdx];
         arr[minIdx] = arr[i] - arr[minIdx];
         arr[i] -= arr[minIdx];
      }
   }
}

int BinarySearch (int* arr, int arrSize, int key) {
   int low = 0, high = arrSize - 1, idx = -1;
   while (low <= high) {
      int mid = low + (high - low) / 2;
      // Checks if key is present at mid and is it's first occurrence
      if (arr[mid] == key) {
         idx = mid;
         high = mid - 1;
      } else if (arr[mid] < key)
         low = mid + 1;
      else
         high = mid - 1;
   }
   return idx;
}