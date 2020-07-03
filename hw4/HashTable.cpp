/*** Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 4
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTable.h"
using namespace std;
HashTable::HashTable( const int tableSize, const CollisionStrategy option ) {
    size = tableSize;
    items = new int*[ tableSize];
    for( int i = 0; i < tableSize; i++) {
        items[i] = new int[2];
        items[i][0] = 0;
        items[i][1] = -1; //all are empty
    }
    collStr = option;
    currItems = 0;
    zeroAdded = false;
}

HashTable::~HashTable() {
    for( int i = 0; i < size; i++)
        delete[] items[i];
    delete[] items;
}

const bool HashTable::isFull() {
    return ( currItems >= size);
}

bool HashTable::insert( const int item) {
    if( isFull()) return false;
    int numProbes; //throwaway
    if( item != 0 && search( item, numProbes)) return false;//if value is already present do not add
    if( item == 0 && collStr == DOUBLE) return false;
    if( item == 0 && zeroAdded) return false;
    if( item == 0) zeroAdded = true;
    //primary hash function is mod
    int address      = item % size;
    bool found = true; //throwaway bool
    if( items[ address][1] == 1) {//if occupied
        probe( address, item, 0, found, 1);
        if( address == item % size) //no change was made, meaning that the probe func stalled
            return false;
    }
    items[ address][0] = item;
    items[ address][1] = 1;
    currItems++;
    return true;
}
/**
* returns -1 if insertion is not possible
*/
const int HashTable::probe( int& address, const int item,
                        const int searchFor, bool& found, bool forInsertion) {
    int probationCount = 1;
    bool passForZero = ( searchFor == 0) && !forInsertion;//this is for when we search for or remove 0
    if( collStr == LINEAR) {
        while( passForZero || ( items[address][0] != searchFor) || (forInsertion && items[address][0] == 0 && items[address][1] == 1) ) {
            if( !forInsertion && searchFor == 0 && items[address][1] == 1 && items[address][0] == 0) {
                passForZero = false;
                break;
            }
            address++;
            address = ( address) % size;
            probationCount++;
            if( items[address][1] == -1  || probationCount > 13) {//if empty, we do not take deleteds into account
                if( !passForZero || probationCount > 13){
                    found = false;
                    break;
                }
            }
        }
    }
    else if( collStr == QUADRATIC) {
        while( passForZero || (items[address][0] != searchFor) || (forInsertion && items[address][0] == 0 && items[address][1] == 1) ) {
            if( !forInsertion && searchFor == 0 && items[address][1] == 1 && items[address][0] == 0) {
                passForZero = false;
                break;
            }
            address = (( item % size) + probationCount*probationCount) % size;
            probationCount++;
            if( items[address][1] == -1  || probationCount > 13) {//if empty, we do not take deleteds into account
                found = false;
                break;
            }
        }
    }
    else if( collStr == DOUBLE) {
        int hash2 = secHash( item);

        while( items[address][0] != searchFor ) {
            if( hash2 % size == 0 || hash2 == item % size) {
                if( items[address][0] != searchFor)
                    found = false;
                break;
            }
            address = (( item % size) + probationCount*hash2) % size;
            if( items[address][1] == -1 || probationCount > 13) {//if empty, we do not take deleteds into account
                found = false;            //end probing
                break;
            }
            probationCount++;
        }
    }
    return probationCount; //i is the number of probes
}
//reverse the item
const int HashTable::secHash( int item) {
    int temp = 0;
    while( item) {
        temp = temp*10 + item % 10;
        item /= 10;
    }
    return temp;
}

bool HashTable::search( const int item, int& numProbes ) {
    int address = item % size;
    numProbes = 1;
    bool found = true;
    if( items[ address][0] != item || (item == 0 && items[ address][1] != 1)) {
        if( items[address][1] == -1) //if this specific node is empty, therefore not found
            return false;
    }
    //if we look for 0, we take a different approach
    numProbes = probe( address, item, item, found, 0);
    return found;
}

bool HashTable::remove( const int item ) {
    bool found = true;
    int numProbes;//throwaway
    if( !search( item, numProbes)) return false;
    //this means that the value is present no matter what
    int  address = item % size;
    if( items[ address][0] != item || ( items[address][0] == item && item == 0))
        probe( address, item, item, found, 0);
    if( items[ address][1] == 1) {
        items[ address][0] = 0;//delete node
        items[ address][1] = 0;//deleted
    }
    currItems--;
    return found;
}

void HashTable::display() {
    for( int i = 0; i < size; i++) {
        cout<<i<<":\t";
        if( items[i][1] == 1) cout<<items[i][0];
        cout<<endl;
    }
}

void HashTable::analyze( double& numSuccProbes, double& numUnsuccProbes ) {
    int totSucc   = totalSucc();
    numSuccProbes = ((double) totSucc )/(double) currItems;

    numUnsuccProbes = 0;
    if( collStr == DOUBLE) {
        numUnsuccProbes = -1;
        return;
    }
    int  address;
    bool found;//throwaway
    int  totalUnsucc = 0; //since we search for empty nodes, if all is empty, then we need 0 probes
    for( int i = 0; i < size; i++) {
        address = i;
        if( i == 0) address += size;//much like addition, searching for 0 also requires many more probes than usual
        int unsucc;
        if( search( address, unsucc)) {//if the number is actually inside the search function
            while( search( address, unsucc)) address += size;
        }
        cout<<address<<": "<<unsucc<<endl;
        totalUnsucc += unsucc;
    }
    numUnsuccProbes = ((double) totalUnsucc) / (double) size;

}
//returns total number of probes for the successful searches
const int HashTable::totalSucc() {
    int totalProbes = 0;
    for( int i = 0; i < size; i++) {
        if( items[i][1] == 1) {
            int probeCount = 0;
            search( items[i][0], probeCount);
            totalProbes += probeCount;
        }
    }
    return totalProbes;
}

const int HashTable::getOpNumber( const string line) {
    int i = 1;
    int beforeTabOrSpaceIndex = 0;
    int afterTabOrSpaceIndex = 0;
    while( line[i] && ( line[i] == ' ' || line[i] == '\t')) {//go through the loop until
        i++;                                   //a space or tab does not occur
    }
    beforeTabOrSpaceIndex = i;

    while( line[i] && !( line[i] == ' ' || line[i] == '\t')) {//go through the loop until
        i++;                                   //a space or tab DOES occur
    }
    afterTabOrSpaceIndex = i;
    //below is to convert from string to integer
    int temp;
    istringstream( line.substr( beforeTabOrSpaceIndex, afterTabOrSpaceIndex - beforeTabOrSpaceIndex + 1)) >> temp;
    return temp;
}

void HashTable::readFromFile( const string fileName) {
    fstream file(fileName.c_str());
    string line;
    int valToOperate;
    bool result;
    while( getline( file, line)) {
        if( line[0] == 'S') {//i wrote the next line thrice because I want
                             //to eliminate the lines where other information
                             //is written, like if a first line exists like
                             //Operation 'tab' Meaning etc.
            valToOperate = getOpNumber( line);
            int numProbes = 0;
            result       = search( valToOperate, numProbes);

            if( result) cout<<valToOperate<<"\tfound after "<<numProbes<<" probes"<<endl;
            else        cout<<valToOperate<<"\tnot found after "<<numProbes<<" probes"<<endl;
        }
        else if( line[0] == 'D') {
            valToOperate = getOpNumber( line);
            result       = remove( valToOperate);

            if( result) cout<<valToOperate<<"\tdeleted"<<endl;
            else        cout<<valToOperate<<"\tnot deleted"<<endl;
        }
        else if( line[0] == 'I') {
            valToOperate = getOpNumber( line);
            result       = insert( valToOperate);
            if( result) cout<<valToOperate<<"\tinserted"<<endl;
            else        cout<<valToOperate<<"\tnot inserted"<<endl;
        }
    }
}
