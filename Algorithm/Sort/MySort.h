#ifndef MY_SORT_H
#define MY_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Swap(int* a, int* b);
void InsertionSort(int arr[], int len);
void BubbleSort(int arr[], int len);
void QuickSort(int arr[], int st, int en);
int _SetPivot(int arr[], int st, int en);

#endif