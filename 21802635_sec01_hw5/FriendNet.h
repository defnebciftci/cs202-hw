/*** Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 5
*/
#include <string>
using namespace std;
class FriendNet{
public:
    FriendNet                 ( const string fileName);// constructor
    FriendNet                 ( const FriendNet& aNet);// copy constructor
    ~FriendNet();// destructor
    void listFriends          ( const string personName, const int hopNo);
    void displayAverageDegrees();
    void displayDiameters     ();
private:// ...
    // define your data members here
    struct Node {
        string  name;
        int     id;
        int     degree;
        Node*   next;
    };
    Node** adjList = NULL;
    int       size = 0;
    // define private class functions here, if you have any
    // YOU HAVE TO USE THE ADJACENCY LIST REPRESENTATION
/**
* The implementation is like this:
* An adjacency matrix of booleans is used to determine whether people are connected are not
* A matrix is used instead of a linked list because of a possibly too large list being inputted
* The studentNames string array holds the student names in the order of their IDs
*/
    void            readFromFile        ( const string );
    const int       readFirstLine       ( const string ); //returns how many people there are
    void            getNextLines        ( const string, const int );
	void            visitForDegree      ( bool*&, int, int&, int&);
	void            visitManyTimes      ( int, const int, bool*& );
	void            visitForComponents  ( int, bool* ) ;
	int             visitForEachShortest( bool*&, bool*& ) ;
	void            visitForShortest    ( const int, const int, bool*, int, int*&) ;
};
