/*** Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 4
*/
#include "HashTable.h"
#include <iostream>
#include <stdio.h>
using namespace std;
int main() {
    int tableSize = 13;
    cout<<"LINEAR PROBING"<<endl;
    HashTable table1( tableSize , LINEAR);
    table1.readFromFile( "itemop.txt");
    cout<<"\nFinal table: "<<endl;
    table1.display();
    double numSucc, numUnsucc;
    table1.analyze( numSucc, numUnsucc);
    printf( "Successful average:\t%.1f\nUnsuccessful average:\t%.1f\n\n", numSucc, numUnsucc);

    cout<<"QUADRATIC PROBING"<<endl;
    HashTable table2( tableSize , QUADRATIC);
    table2.readFromFile( "itemop.txt");
    cout<<"\nFinal table: "<<endl;
    table2.display();
    table2.analyze( numSucc, numUnsucc);
    printf( "Successful average:\t%.1f\nUnsuccessful average:\t%.1f\n\n", numSucc, numUnsucc);

    cout<<"DOUBLE HASHING"<<endl;
    HashTable table3( tableSize , DOUBLE);
    table3.readFromFile( "itemop.txt");
    cout<<"\nFinal table: "<<endl;
    table3.display();
    table3.analyze( numSucc, numUnsucc);
    printf( "Successful average:\t%.1f\nNo unsuccessful average calculated\n", numSucc);
    return 0;
}

