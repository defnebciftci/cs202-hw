#include <iostream>
using namespace std;

#ifndef HW1PART2_H_INCLUDED
#define HW1PART2_H_INCLUDED
class Sorting {
    public:
        void insertionSort  (int *arr, int size, int &compCount, int &moveCount);
        void quickSort(int *arr, int size, int &compCount, int &moveCount);
        void mergeSort(int *arr, int size, int &compCount, int &moveCount);

    private:
        void merge( int* arr, int first, int mid, int last, int &compCount, int &moveCount);
        void mergeSortHelper(int *arr, int first, int last, int &compCount, int &moveCount);
        void swapping( int* arr, int firstIndex, int secIndex, int &moveCount);
        void partition( int* arr, int first, int last, int &compCount, int &moveCount, int &pivotIndex);
        void quickSortHelper( int* arr, int first, int last, int &compCount, int &moveCount);
};
#endif // SJDSG_H_INCLUDED


