/*** Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 5
*/
#include "FriendNet.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <climits>
using namespace std;

FriendNet::FriendNet(const string fileName) {
    readFromFile( fileName);
}

FriendNet::FriendNet( const FriendNet& aNet) {
    this->~FriendNet();
    this->size = aNet.size;
    this->adjList = new Node*[ size];
    Node* curr;
    Node* toCopy;

    for( int i = 0; i < size; i++) {//hard copy
        curr         = new Node;
        adjList[ i]  = curr;
        toCopy       = aNet.adjList[ i];
        curr->    id = toCopy->id;
        curr->degree = toCopy->degree;
        curr->  name = toCopy->name;
        while( toCopy->next) {
            curr->next = new Node;
            curr       = curr->next;
            toCopy     = toCopy->next;
            curr->  id = toCopy->id;
        }
        curr->    next = NULL;
    }
    //aNet.~FriendNet();
}

void FriendNet::readFromFile( const string fileName) {
    fstream file( fileName.c_str());
    string line;
    //first line is how many people there are,i.e. the both dimensions of the matrix
    getline( file, line);

    size = readFirstLine( line);
    adjList = new Node*[size];
    int sizeTemp = size;
    //we got to the firstline, now to the next lines
    //we will use dim to check since it is not used anymore at this point
    sizeTemp--;
    while( sizeTemp >= 0) {
        getline( file, line);
        getNextLines( line, size - sizeTemp - 1);
        sizeTemp--;
    }
}

void FriendNet::listFriends(const string personName, const int hopNo) {
    bool     found = false;
    bool* adjacent = new bool[ size];

    for( int i = 0; i < size; i++) adjacent[ i] = false; //init as false

    int howManyFriends = 0;
    int              i = 0;
    for( ; i < size && !found; i++) {
        if( personName.compare( adjList[ i]->name) == 0) found = true;
    } //the id on found is at the index we are looking for
    i--;
    if( !found) {
        cout<<personName<<" does not exist in the network."<<endl;
        delete[] adjacent;
        return;
    }
    //the person is found and is inside adjList[i]

    cout<<"People accessible from "<<personName<<" within "<<hopNo<<" hops: ";
    if( hopNo <= 0) {
        cout<<"NOBODY"<<endl;
        delete[] adjacent;
        return;
    }
    visitManyTimes( hopNo, i, adjacent);
    int index = i;

    for( int i = 0; i < size; i++)
        if( adjacent[ i] && i != index) howManyFriends++;

    if( howManyFriends == 0) cout<<"NOBODY"<<endl;
    else {
        for( int i = 0; i < size; i++) {
            if( adjacent[ i] && i != index) {
                cout<<adjList[ i]->name;
                howManyFriends--;
                if( howManyFriends <= 0) cout<<endl;
                else                     cout<<", ";
            }
        }
    }
    delete[] adjacent;
}

void FriendNet::visitManyTimes( int hopNo, const int index, bool*& visited) {
    Node* curr = adjList[ index];
    visited[ index] = true;
    int     id = 0;
    hopNo--;
    if( hopNo == 0) {
        while( curr->next) {
            curr = curr->next;
            id   = curr->id;
            visited[ id] = true;
        }
    }
    else {
        while( curr->next) {
            curr = curr->next;
            id   = curr->id;
            visitManyTimes( hopNo, id, visited);
        }
    }
}

const int FriendNet::readFirstLine( const string line) {
    int i = 0;
    int beforeTabOrSpaceIndex = 0;
    int afterTabOrSpaceIndex = 0;
    int howManyPeople = 0;

    while( line[i]) {
        while( line[i] && ( line[i] == ' ' || line[i] == '\t')) {//go through the loop until
            i++;                                   //a space or tab does not occur
        }
        beforeTabOrSpaceIndex = i;

        while( line[i] && !( line[i] == ' ' || line[i] == '\t')) {//go through the loop until
            i++;                                   //a space or tab DOES occur
        }
        afterTabOrSpaceIndex = i;
        istringstream( line.substr( beforeTabOrSpaceIndex, afterTabOrSpaceIndex - beforeTabOrSpaceIndex + 1)) >> howManyPeople;
        return howManyPeople;
    }
}

void FriendNet::displayDiameters() {
    int*     weight = new int [ size];
    bool* vertexSet = new bool[ size];
    bool*   visited = new bool[ size];
    int* weightList = new int [ size];
    bool*     comps = new bool[ size];

    for( int i = 0; i < size; i++) {
        weight      [ i] = INT_MAX;
        visited     [ i] = false;
        vertexSet   [ i] = false;
        weightList  [ i] = 0;
        comps       [ i] = false;
    }

    int componentCount = 0;
    string result = "";

    for( int i = 0; i < size; i++) {
        if( !vertexSet[ i]) {
            componentCount++;
            visitForComponents( i, comps);
            int max = visitForEachShortest( comps, vertexSet);

            if( max == INT_MIN) max = 0;
            weightList[ componentCount - 1] = max;

            for( int k = 0; k < size; k++) comps[ k] = false;
        }
    }
    cout<<"There are "<<componentCount<<" connected components.";
    if( componentCount > 0)  cout<<"The diameters are:";
    cout<<endl;
    for( int i = 0; i < componentCount; i++)
        printf( "For component %d: %d\n", i, weightList[ i]);

    delete[] weight    ;
    delete[] vertexSet ;
    delete[] visited   ;
    delete[] weightList;
    delete[] comps     ;
}

void FriendNet::visitForShortest( const int index, const int firstId, bool* visited, int count, int*& weight) {
    Node* curr = adjList[ index];

	if( !visited[ index]) {
		visited  [ index] = true;

        int id = 0;

        count++;
        while( curr->next) {
            curr = curr->next;
            id   = curr->id;
            if( count < weight[ id] && id != firstId) {
                weight[ id] = count;
            }
            visitForShortest( id, firstId, visited, count, weight);
        }
        visited[ index] = false;//set to false when going back
	}
}

int FriendNet::visitForEachShortest( bool*& components, bool*& alreadyVisited) {
    int       max = INT_MIN;
    int*   weight = new int [ size];
    bool* visited = new bool[ size];

    for( int i = 0; i < size; i++) {
        if( components[ i]) {
            for( int k = 0; k < size; k++) {
                weight [ k] = INT_MAX;
                visited[ k] = false;
            }
            visitForShortest( i, i, visited, 0, weight);
            for( int k = 0; k < size; k++)
                if( max < weight[ k] && weight[ k] != INT_MAX) {
                    max = weight[ k];
                }
        }
    }
    for( int i = 0; i < size; i++) if( components[ i]) alreadyVisited[ i] = true;
    delete[] weight;
    delete[] visited;
    return max;
}

void FriendNet::visitForComponents( int index, bool* visited) {
    Node* curr = adjList[ index];

	if( !visited[ index]) {
		visited  [ index] = true;

        int id = 0;

        while( curr->next) {
            curr = curr->next;
            id   = curr->id;
            visitForComponents( id, visited);
        }
	}
}

void FriendNet::getNextLines( const string line, const int index) {
    Node* current = new Node;
    int i = 0;
    int beforeTabOrSpaceIndex = 0;
    int afterTabOrSpaceIndex = 0;
    int countForString = 0;

    int id = 0, degree = 1;

    while( line[i]) {
        while( line[i] && ( line[i] == ' ' || line[i] == '\t')) {//go through the loop until
            i++;                                   //a space or tab does not occur
        }
        beforeTabOrSpaceIndex = i;

        while( line[i] && !( line[i] == ' ' || line[i] == '\t')) {//go through the loop until
            i++;                                   //a space or tab DOES occur
        }
        afterTabOrSpaceIndex = i;
        string substring = line.substr( beforeTabOrSpaceIndex, afterTabOrSpaceIndex - beforeTabOrSpaceIndex + 1);
        countForString++;//first one is id, second one is name, third one is degree
        if( countForString == 2) {
            substring.erase( remove( substring.begin(), substring.end(), ' ' ), substring.end());
            substring.erase( remove( substring.begin(), substring.end(), '\t'), substring.end());
            current->name = substring;
        }
        else {
            int temp;
            istringstream( substring) >> temp;
            if( countForString == 1) {
                id = temp;
                current->id = id;
                adjList[ index] = current;
            }
            else if( countForString == 3) {
                degree = temp;
                current->degree = degree;
            }
            else if( degree > 0) {//now on to the degrees
                current->next = new Node;
                current->next->id = temp;
                current = current->next;
                degree--;
            }

            if( degree <= 0) {
                current = NULL;
                break;
            }
        }
    }
    delete current;
}

FriendNet::~FriendNet() {
    for( int i = 0; i < size; i++) {
        Node* curr = adjList[ i];
        while( curr->next) {
            delete curr;
            curr = curr->next;
        }
        delete curr;
    }
    if( adjList != NULL) delete[] adjList;
}


void FriendNet::visitForDegree( bool*& visited, int index, int& count, int& studentCount) {
	if( visited[ index] == false) {
        Node* curr       = adjList[ index];
        int degree = curr->degree;
		count += degree;
		studentCount++;
		visited [ index] = true;

        int id = 0;

        while( degree > 0) {
            curr = curr->next;
            id   = curr->id;
            degree--;
            visitForDegree( visited, id, count, studentCount);
        }
	}
}

void FriendNet::displayAverageDegrees() {
    int count          = 0;
	int componentCount = 0;
	bool* visited      = new bool[ size];
	double* components = new double[ size];

	for( int i = 0; i < size; i++) {
		visited[ i] = false;
	}

	for( int i = 0; i < size; i++) {
        int studentCount = 0;
        count = 0;
		if( !visited[ i]) {
			visitForDegree( visited, i, count, studentCount);
			componentCount++;
			components[ componentCount - 1] = ((double) count)/(double) studentCount;
		}
	}
    cout<<"There are "<<componentCount<<" connected components.";
    if( componentCount > 0)  cout<<"The degrees are: ";
    cout<<endl;
    for( int i = 0; i < componentCount; i++) {
        printf( "For component %d : %.2f\n", i, components[ i]);
    }
    delete[] visited;
    delete[] components;
}
