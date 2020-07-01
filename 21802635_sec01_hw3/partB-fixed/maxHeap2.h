/** * Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 3
*/
#include <string>
#include "Patient.h"
using namespace std;

class Heap { //we are creating a priority queue basically
public:
    ~Heap();
    /**destroy the priority queue*/
    void destroy();
    /**determines whether the queue is empty or not*/
    const bool isEmpty();
    /**– returns the item in a priority queue with the highest
    priority value, and deletes that item from the priority queue.*/
    Patient deleteHeap();
    void printHeap();
    void insertHeap( const int id, const int priority, const int arrivalTime, const int serviceTime);
private:
    void create();
    void rebuildHeap( const int);
    const int INIT_SIZE = 10;
    Patient* patients; //dynamically allocated array
    int size = 0; //this is to count how many elements are present
    int arraySize = 0; //This is for the size of patients allocated array
};
