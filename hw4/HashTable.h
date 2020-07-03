/*** Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 4
*/
enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
#include <string>
using namespace std;
/**
* items[i][1] values:
* Empty   : -1
* Deleted : 0
* Occupied: 1
* HashTable implementation with only integer items
* array with given size (tableSize) upon construction
* mod is the primary hash(key) operation (key mod tableSize)
* if said key is full, it uses a separate function f for this strategy
* hi(key) = (hash(key) + f(i)) mod tableSize
* where hi is the array index used and i is the iteration number
* linear probing, quadratic probing, double hashing all used
*/
class HashTable {
public:
    /**
    * Constructor that initializes the hash table with the given size.
    * The collision resolutionstrategy is given as an option that will be used
    * in the insert, delete, and search operations.
    */
    HashTable( const int tableSize, const CollisionStrategy option );
    /**
    * Destructor that cleans up any dynamic memory used.
    */
    ~HashTable();
    /**
    * Inserts the given item (also used as the key value) into the hash table
    * and returns true if insertion is successful, and false otherwise.
    */
    bool insert( const int item );
    /**
    * Deletes the given item from the hash table, and returns true if deletion
    * is successful, and false otherwise
    */
    bool remove( const int item );
    /**
    * Searches the given item in the hash table, and returns true if
    * search is successful (i.e., the item is found), and false otherwise.
    * This function also returns the number of probes used during the
    * search for this item.
    */
    bool search( const int item, int& numProbes );
    /**
    * Displays the contents of the hash table
    * (In each line, the first value indicates the array index, followed by colon, followed by theitem value stored at that index (no item value is shown if the cell is empty).)
    */
    void display();
    /**
    * Analyzes the current hash table in terms of the average number of
    * probes for successful and unsuccessful searches, and returns these
    * two values in the variables passed by reference.
    * For analyzing the performance for successful searches, you can
    * use the item values currently stored in the table for searching.
    * For analyzing the performance of unsuccessful searches,you can
    * initiate a search that starts at each array location (index),
    * and count the number of probes needed to reach an empty location
    * in the array for each search.
    */
    void analyze( double& numSuccProbes, double& numUnsuccProbes );
    void readFromFile( const string fileName);
private:
    int** items;
    int size;
    int currItems;
    CollisionStrategy collStr;
    const bool isFull();
    const int probe( int& address, const int item, const int searchFor, bool& found, bool);
    const int secHash( int item);
    const int totalSucc();
    const int getOpNumber( const string line) ;
    bool zeroAdded; //to check whether 0 was added once or not, as it is hard to check
};
