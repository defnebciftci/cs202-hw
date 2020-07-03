/** * Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 3
*/
#include "maxHeap1.h"
#include <string> //string
#include <iostream> //for NULL

using namespace std;

Heap::~Heap() {

}

void Heap::create() {
//    patients = new Patient[ MAX_SIZE];
}

const bool Heap::isEmpty() {
    return (size == 0);
}

void Heap::insertHeap( const int id, const int priority, const int arrivalTime, const int serviceTime) throw ( HeapException){
    if( size == 0)   create();
    if( size == MAX_SIZE) {//should not be larger than 2000
        throw "HeapException: Heap is full";
    }
    //initialize new patient
    Patient patientToAdd( id, priority, arrivalTime, serviceTime);
    if( size == 0) { //first element of heap
        patients[0] = patientToAdd;
    }
    else {//add to last, then check for priorities
        int indexToAdd = size; //index to add the new patient
        int parentIndex = (size- 1) / 2;
        bool parentIsBigger = false;
        while( !parentIsBigger) {
            parentIsBigger = patients[ parentIndex].isPrioritizedOver( patientToAdd);
            if( !parentIsBigger) {//we found where to add
                patients[ indexToAdd] = patients[parentIndex];
                indexToAdd  = parentIndex;
            }
            if( parentIndex == 0) parentIsBigger = true; //to end the loop
            else                  parentIndex = (parentIndex - 1) / 2; //it will always be 0 once it reaches to 0
        }
        patients[ indexToAdd] = patientToAdd;
    }
    size++;
}
//you delete from the root and then rebuild the heap structure
Patient Heap::deleteHeap() {
    Patient temp = patients[0];
    //move the last element into the root, now this is a semiheap
    patients[0] = patients[ size - 1];
    //now we rebuild the heap
    rebuildHeap( 0);
    //decrement the size
    size--;
    //rebuildHeap( 0);
    return temp;
}

const int power( const int times, const int base) {
    int basebase = 1;
    for(int i = 0; i < times; i++) {
        basebase *= base;
    }
    return basebase;
}
//recursive call
void Heap::rebuildHeap( int index) {
    if( index >= size) return;
    int rightIndex = index*2 + 2;
    int leftIndex  = index*2 + 1;

    if     ( leftIndex < size && patients[ leftIndex].isPrioritizedOver( patients[ index])) {
        Patient temp = patients[index];
        patients[ index] = patients[ leftIndex];
        patients[ leftIndex] = temp;
        rebuildHeap( leftIndex);
    }

    if( rightIndex < size && patients[ rightIndex].isPrioritizedOver( patients[ index])) {
        Patient temp = patients[index];
        patients[ index] = patients[ rightIndex];
        patients[ rightIndex] = temp;
        rebuildHeap( rightIndex);
    }
}

void Heap::printHeap() {
    for( int i = 0; i < size; i++) cout<<patients[i]<<" ";
    cout<<endl;
}

