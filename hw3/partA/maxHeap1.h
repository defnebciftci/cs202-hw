/** * Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 3
*/
#include <string>
#include "Patient.h"
using namespace std;

struct HeapException : public exception {
};

class Heap { //we are creating a priority queue basically
public:
    ~Heap();
    void create();
    /**destroy the priority queue*/
    void destroy();
    /**determines whether the queue is empty or not*/
    const bool isEmpty();
    /**– returns the item in a priority queue with the highest
    priority value, and deletes that item from the priority queue.*/
    Patient deleteHeap();
    void printHeap();
    void insertHeap( const int id, const int priority, const int arrivalTime, const int serviceTime) throw(HeapException);
private:
    void rebuildHeap( const int);
    const static int MAX_SIZE = 2000;
    Patient patients[MAX_SIZE];
    int size = 0;
};
