#include <iostream>
#include "sorting.h"
using namespace std;

void Sorting::insertionSort  (int *arr, int size, int &compCount, int &moveCount) {

    for( int j = 1; j < size; j++) {
        int key = arr[j];
        int i = j - 1;
        for( ; i >= 0 && arr[i] > key; i--, compCount++) {
            moveCount++;
            arr[i + 1] = arr[ i];
        }
        if( i >= 0)
            compCount++;
        arr[ i + 1] = key;
    }
}
void Sorting::swapping( int* arr, int firstIndex, int secIndex, int &moveCount) {
    int temp         = arr[ firstIndex];
    arr[firstIndex] = arr[secIndex];
    arr[secIndex]   = temp;
    moveCount++;
}
void Sorting::partition( int* arr, int first, int last, int &compCount, int &moveCount, int &pivotIndex) {
    int pivot = arr[ first];
    int lastS1 = first;
    int firstUnknown = first + 1;

    for( ; firstUnknown <= last; firstUnknown++, compCount++) {
        if( arr[ firstUnknown] < pivot) {
            ++lastS1;
            swapping( arr, firstUnknown, lastS1, moveCount);
        }
    }
    swapping( arr, first, lastS1, moveCount);
    pivotIndex = lastS1;
}
void Sorting::quickSortHelper( int* arr, int first, int last, int &compCount, int &moveCount) {
    if( first < last) {
        int pi;
        partition( arr, first, last, compCount, moveCount, pi);

        quickSortHelper( arr, first, pi - 1, compCount, moveCount);
        quickSortHelper( arr, pi + 1, last, compCount, moveCount);
    }
}
void Sorting::quickSort(int *arr, int size, int &compCount, int &moveCount) {
    quickSortHelper( arr, 0, size - 1, compCount, moveCount);
}

void Sorting::merge( int* arr, int first, int mid, int last, int &compCount, int &moveCount) {
    int size1 = mid - first + 1;
    int size2 = last - mid;

    int temp1[ size1], temp2[ size2];

    for( int i = 0; i < size1; i++) temp1[ i] = arr[ i + first];
    for( int j = 0; j < size2; j++) temp2[ j] = arr[ j + mid + 1];

    int first1 = 0;
    int first2 = 0;
    int index = first;
    while( first1 < size1 && first2 < size2) {
        if( temp1[ first1] <= temp2[first2]) {
            arr[ index] = temp1[ first1];
            first1++;
            moveCount++;
        }
        else {
            arr[ index] = temp2[ first2];
            first2++;
        }
        index++;
        compCount++;
    }

    while( first1 < size1) {
        arr[ index] = temp1[first1];
        first1++;
        index++;
        compCount++;
    }

    while( first2 < size2) {
        arr[ index] = temp2[first2];
        first2++;
        index++;
        compCount++;
    }
}
/**
first is the first index, last is the last index
*/
void Sorting::mergeSortHelper(int *arr, int first, int last, int &compCount, int &moveCount) {
    if( first == last) return;

    int mid = (first + last) / 2;

    mergeSortHelper( arr, first, mid, compCount, moveCount);
    mergeSortHelper( arr, mid + 1, last, compCount, moveCount);
    merge( arr, first, mid, last, compCount, moveCount);
}

void Sorting::mergeSort(int *arr, int size, int &compCount, int &moveCount) {
    mergeSortHelper( arr, 0, size - 1, compCount, moveCount); //last is the last index
}
