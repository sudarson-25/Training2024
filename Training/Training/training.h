#pragma once
// ------------------------------------------------------------------------------------------------
// Training ~ A training program for new joiners at Metamation, Batch - July 2024.
// Copyright (c) Metamation India.
// ------------------------------------------------------------------
// training.h
// Contains function signatures
// Sudarson S
// ------------------------------------------------------------------------------------------------
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/// <summary>Implements binary search algorithm </summary>
int BinarySearch (int* arr, int arrSize, int key);

/// <summary>Implements selection sort algorithm </summary>
void SelectionSort (int* arr, int n);