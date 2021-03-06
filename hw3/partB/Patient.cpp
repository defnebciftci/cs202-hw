/** * Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 3
*/
#include "Patient.h"

using namespace std;
Patient::Patient() : id(-1), priority(-1), arrivalTime(-1), serviceTime(-1){}

Patient::Patient( const int id, const int priority, const int arrivalTime, const int serviceTime) {
    this->id = id;
    this->priority = priority;
    this->arrivalTime = arrivalTime;
    this->serviceTime = serviceTime;
}

const int Patient::getPriority() {
    return priority;
}

const int Patient::getArrivalTime() {
    return arrivalTime;
}

const int Patient::getServiceTime() {
    return serviceTime;
}

const int Patient::getId() {
    return id;
}

const bool Patient::isPrioritizedOver( const Patient patient1) {
    if( this->priority > patient1.priority) return true;
    else if( this->priority == patient1.priority) {
        if( this->arrivalTime < patient1.arrivalTime) return true;
        else return false;
    }
    else return false;
}

ostream& operator << (ostream &out, const Patient patient) {
    out << "id: "<<patient.id<<" priority: "<<patient.priority;
    out<< " arrival time: "<<patient.arrivalTime<<" service time: "<<patient.serviceTime<<endl;
    return out;
}

Patient& Patient::operator = (const Patient patient) {
    id = patient.id;
    priority = patient.priority;
    arrivalTime = patient.arrivalTime;
    serviceTime = patient.serviceTime;
    return *this;
}
