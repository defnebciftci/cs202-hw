#include <iostream>
#include "sorting.h"
#include "auxArrayFunctions.h"
#include <ctime>
using namespace std;

void analysisHelper(int& compCount1, int& compCount2, int& compCount3,
                    double& timeQuiSorting, double& timeMerSorting, double& timeInsSorting,
                    int& moveCount1, int& moveCount2, int& moveCount3,
                    int size, int nearly) {

    int* arr1 = new int[size];
    int* arr2 = new int[size];
    int* arr3 = new int[size];
    Sorting sorter;
    compCount1 = 0, compCount2 = 0, compCount3 = 0;
    moveCount1 = 0, moveCount2 = 0, moveCount3 = 0;

    if( nearly == 1)      createRandomArrays       ( arr1, arr2, arr3, size);
    else if( nearly == 2) createAlreadySortedArrays( arr1, arr2, arr3, size);
    else                  createNearlySortedArrays( arr1, arr2, arr3, size, size / 2);
    clock_t start = clock();
    for(int i = 0; i < 10; ++i)
        sorter.insertionSort( arr1, size, compCount1, moveCount1);
    clock_t ending = clock();
    timeInsSorting = 1000 * double( ending - start) / (CLOCKS_PER_SEC* 10);

    start = clock();
	for( int i = 0; i < 10; i++)
		sorter.mergeSort( arr1, size, compCount2, moveCount2);
    ending = clock();
    timeMerSorting = 1000 * double( ending - start) / (CLOCKS_PER_SEC*10);

    start = clock();
    sorter.quickSort( arr1, size, compCount3, moveCount3);
    ending = clock();
    timeQuiSorting = 1000 * double( ending - start) / (CLOCKS_PER_SEC);

    deallocateArray( arr1, size);
    deallocateArray( arr2, size);
    deallocateArray( arr3, size);

}

void performanceAnalysis( int nearly) {
    int size1 = 5000;
    int compCount1_5000 = 0, compCount2_5000 = 0, compCount3_5000 = 0;
    int moveCount1_5000 = 0, moveCount2_5000 = 0, moveCount3_5000 = 0;
    double timeQuiSorting5000 = 0, timeMerSorting5000 = 0, timeInsSorting5000 = 0;
    analysisHelper( compCount1_5000, compCount2_5000, compCount3_5000, timeQuiSorting5000, timeMerSorting5000,
                   timeInsSorting5000, moveCount1_5000, moveCount2_5000, moveCount3_5000, size1, nearly);

    const int size2 = 10000;
    int compCount1_10000 = 0, compCount2_10000 = 0, compCount3_10000 = 0;
    int moveCount1_10000 = 0, moveCount2_10000 = 0, moveCount3_10000 = 0;
    double timeQuiSorting10000 = 0, timeMerSorting10000 = 0, timeInsSorting10000 = 0;
    analysisHelper( compCount1_10000, compCount2_10000, compCount3_10000, timeQuiSorting10000, timeMerSorting10000,
                   timeInsSorting10000, moveCount1_10000, moveCount2_10000, moveCount3_10000, size2, nearly);

    const int size3 = 15000;
    int compCount1_15000 = 0, compCount2_15000 = 0, compCount3_15000 = 0;
    int moveCount1_15000 = 0, moveCount2_15000 = 0, moveCount3_15000 = 0;
    double timeQuiSorting15000 = 0, timeMerSorting15000 = 0, timeInsSorting15000 = 0;
    analysisHelper( compCount1_15000, compCount2_15000, compCount3_15000, timeQuiSorting15000, timeMerSorting15000,
                   timeInsSorting15000, moveCount1_15000, moveCount2_15000, moveCount3_15000, size3, nearly);

    const int size4 = 20000;
    int compCount1_20000 = 0, compCount2_20000 = 0, compCount3_20000 = 0;
    int moveCount1_20000 = 0, moveCount2_20000 = 0, moveCount3_20000 = 0;
    double timeQuiSorting20000 = 0, timeMerSorting20000 = 0, timeInsSorting20000 = 0;
    analysisHelper( compCount1_20000, compCount2_20000, compCount3_20000, timeQuiSorting20000, timeMerSorting20000,
                   timeInsSorting20000, moveCount1_20000, moveCount2_20000, moveCount3_20000, size4, nearly);

    const int size5 = 25000;
    int compCount1_25000 = 0, compCount2_25000 = 0, compCount3_25000 = 0;
    int moveCount1_25000 = 0, moveCount2_25000 = 0, moveCount3_25000 = 0;
    double timeQuiSorting25000 = 0, timeMerSorting25000 = 0, timeInsSorting25000 = 0;
    analysisHelper( compCount1_25000, compCount2_25000, compCount3_25000, timeQuiSorting25000, timeMerSorting25000,
                   timeInsSorting25000, moveCount1_25000, moveCount2_25000, moveCount3_25000, size5, nearly);


    cout<<"-----------------------------------------------------\nPart c -Time analysis of InsertionSort"<<endl;
    cout<<"Array Size\tTime Elapsed\tcompCount \tmoveCount"<<endl;
    cout<<"5000\t\t"<<timeInsSorting5000<<"ms\t\t";
                cout<<compCount1_5000<<"\t\t"<<moveCount1_5000<<"\t\t"<<endl;
    cout<<"10000\t\t"<<timeInsSorting10000<<"ms\t\t";
                cout<<compCount1_10000<<"\t\t"<<moveCount1_10000<<"\t\t"<<endl;
    cout<<"15000\t\t"<<timeInsSorting15000<<"ms\t\t";
                cout<<compCount1_15000<<"\t\t"<<moveCount1_15000<<"\t\t"<<endl;
    cout<<"20000\t\t"<<timeInsSorting20000<<"ms\t\t"<<compCount1_20000<<"\t\t"<<moveCount1_20000<<"\t\t"<<endl;
    cout<<"25000\t\t"<<timeInsSorting25000<<"ms\t\t"<<compCount1_25000<<"\t\t"<<moveCount1_25000<<"\t\t"<<endl;

    cout<<"Part c - Time analysis of Merge Sort"<<endl;
    cout<<"Array Size\tTime Elapsed\tcompCount \tmoveCount"<<endl;
    cout<<"5000\t\t"<<timeMerSorting5000<<"ms\t\t";
                cout<<compCount2_5000<<"\t\t"<<moveCount2_5000<<"\t\t"<<endl;
    cout<<"10000\t\t"<<timeMerSorting10000<<"ms\t\t";
                cout<<compCount2_10000<<"\t\t"<<moveCount2_10000<<"\t\t"<<endl;
    cout<<"15000\t\t"<<timeMerSorting15000<<"ms\t\t";
                cout<<compCount2_15000<<"\t\t"<<moveCount2_15000<<"\t\t"<<endl;
    cout<<"20000\t\t"<<timeMerSorting20000<<"ms\t\t"<<compCount2_20000<<"\t\t"<<moveCount2_20000<<"\t\t"<<endl;
    cout<<"25000\t\t"<<timeMerSorting25000<<"ms\t\t"<<compCount2_25000<<"\t\t"<<moveCount2_25000<<"\t\t"<<endl;

    cout<<"Part c - Time analysis of Quick Sort"<<endl;
    cout<<"Array Size\tTime Elapsed\tcompCount \tmoveCount"<<endl;
    cout<<"5000\t\t"<<timeQuiSorting5000<<"ms\t\t";
                cout<<compCount3_5000<<"\t\t"<<moveCount3_5000<<"\t\t"<<endl;
    cout<<"10000\t\t"<<timeQuiSorting10000<<"ms\t\t";
                cout<<compCount3_10000<<"\t\t"<<moveCount3_10000<<"\t\t"<<endl;
    cout<<"15000\t\t"<<timeQuiSorting15000<<"ms\t\t";
                cout<<compCount3_15000<<"\t\t"<<moveCount3_15000<<"\t\t"<<endl;
    cout<<"20000\t\t"<<timeQuiSorting20000<<"ms\t\t"<<compCount3_20000<<"\t\t"<<moveCount3_20000<<"\t\t"<<endl;
    cout<<"25000\t\t"<<timeQuiSorting25000<<"ms\t\t"<<compCount3_25000<<"\t\t"<<moveCount3_25000<<"\t\t"<<endl;

}

int main() {
    int size = 16;
    int arr[16] = {9, 5, 8, 15, 16, 6, 3, 11, 18, 0, 14, 17, 2, 9, 11, 7};
    int* arr1 = arr;
    int* arr2 = arr;
    int* arr3 = arr;
    Sorting sorter;
    int compCount1 = 0, compCount2 = 0, compCount3 = 0;
    int moveCount1 = 0, moveCount2 = 0, moveCount3 = 0;

    cout<<"Insertion sort: "<<endl;
    sorter.insertionSort( arr1, size, compCount1, moveCount1);
    displayArray( arr1, size);
    cout<<"Number of key comparisons: "<<compCount1<<endl;
    cout<<"Number of move counts: "<<moveCount1<<endl;

    cout<<"Merge sort: "<<endl;
    sorter.mergeSort( arr2, size, compCount2, moveCount2);
    displayArray( arr2, size);
    cout<<"Number of key comparisons: "<<compCount2<<endl;
    cout<<"Number of move counts: "<<moveCount2<<endl;

    cout<<"Quick sort: "<<endl;
    sorter.quickSort( arr3, size, compCount3, moveCount3);
    displayArray( arr3, size);
    cout<<"Number of key comparisons: "<<compCount3<<endl;
    cout<<"Number of move counts: "<<moveCount3<<endl;

    cout<<"Random arrays: "<<endl;
    performanceAnalysis( 1);
    cout<<"Already sorted arrays: "<<endl;
    performanceAnalysis( 2);
    cout<<"Nearly sorted arrays: "<<endl;
    performanceAnalysis( 3);
    return 0;
}
