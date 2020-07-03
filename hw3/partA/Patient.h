/** * Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 3
*/
#include <iostream>
using namespace std;

class Patient {
public:
    Patient();
    Patient( const int, const int, const int, const int);
    const int getPriority();
    const int getArrivalTime();
    const int getId();
    const int getServiceTime();
    const bool isPrioritizedOver( const Patient patient1);
    friend ostream& operator << (ostream &out, const Patient patient);
private:
    int id;
    int priority;
    int arrivalTime;
    int serviceTime;
};
