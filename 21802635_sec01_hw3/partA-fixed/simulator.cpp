/** * Author: Defne Betül Çiftci
* ID: 21802635
* Section: 1
* Assignment: 3
*/
#include "maxHeap1.h"
#include <bits/stdc++.h> //for INT_MAX
#include <fstream> //for file reading
#include <iostream> //cout
#include <cstring> //c_str()
#include <sstream> //stringstream
#include <string>
using namespace std;


int convertLineToArr( const string line, const int howManyAttributes, Patient& patient) {
    int i = 0;
    int beforeTabOrSpaceIndex = 0;
    int afterTabOrSpaceIndex = 0;
    int attributeCount = 0;
    int attributes[4];

    while( line[i]) {
        if( attributeCount >= howManyAttributes) break;
        while( line[i] && line[i] == ' ' || line[i] == '\t') {//go through the loop until
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

        if( howManyAttributes == 1) {
            return temp;
        }
        else {
            attributes[ attributeCount % 4] = temp;
        }
        attributeCount++;
    }
    Patient temp( attributes[0], attributes[1], attributes[2], attributes[3]);
    patient = temp;
}

int doctorTakesPatients( const int currHeapSize, const int numOfDocsTakingCareOfPpl, Heap& heap, int& patientCount,
                         int*& serviceTimes, const int timePast, string& returnStr) {

    //we need patCountOverall count for calculating the average
    int  sumOfWait = 0;

    //loop goes on for which one is less - number of patients or number of docs
    for( int i = 0; i < numOfDocsTakingCareOfPpl; i++) {
        if( serviceTimes[i] <= 0 && !heap.isEmpty()) { //if there are available doctors and also if there are patients
            Patient patient = heap.deleteHeap();       //to take care of
            serviceTimes[i] = patient.getServiceTime(); //now this specific doctor is taking care of this patient
            int wait = (timePast - patient.getArrivalTime());

            stringstream ss1;
            string s1;
            stringstream ss2;
            string s2;
            stringstream ss3;
            string s3;
            stringstream ss4;
            string s4;

            returnStr += "Doctor ";

            ss1<<i;
            ss1>>s1;

            returnStr += s1;
            returnStr += " takes patient ";

            ss2<<patient.getId();
            ss2>>s2;

            returnStr += s2;
            returnStr +=" at minute ";

            ss3<<timePast;
            ss3>>s3;

            returnStr += s3;
            returnStr += " (wait: ";

            ss4<<wait;
            ss4>>s4;

            returnStr += s4;
            returnStr += " mins)\n";

            patientCount--;

            sumOfWait += wait;
        }
    }
    return sumOfWait;
}

string run( const string fileName, Heap heap, const int numOfDocs, const int maxWait, double& avgWait) {
    fstream file1( fileName.c_str());
    if( !file1) {
        avgWait = -1;
        return "Invalid file name!";
    }
    string               line = "";

    int          patientCount = 0;
    int*         serviceTimes = new int[ numOfDocs];
    int              timePast = 1;
    int         currHeapSize  = 0;
    int             lineCount = 0;
    int       patCountOverall = 1; //to calculate the average waiting time
    string          returnStr = "";
    Patient           tempPat;

    getline( file1, line);
    patientCount    = convertLineToArr( line, 1, tempPat); //we are only gonna add the first number we see which will be the patient count
    lineCount       = patientCount;
    patCountOverall = patientCount;

    for( int i = 0; i < numOfDocs; i++) {
        serviceTimes[i] = 0;
    }

    int i = patientCount;

    while( patientCount > 0) {
        int howManyPatientsAtOnce = 0;
        //first line
        if( tempPat.getArrivalTime() == -1) {
            getline( file1, line);
            convertLineToArr( line, 4, tempPat);
        }
        //first and next lines
        while( lineCount > 0 && tempPat.getArrivalTime() <= timePast) {
            heap.insertHeap( tempPat.getId(), tempPat.getPriority(), tempPat.getArrivalTime(), tempPat.getServiceTime());
            if( getline( file1, line)) {
                convertLineToArr( line, 4, tempPat);
            }
            lineCount--;
            howManyPatientsAtOnce++;
        }

        avgWait += doctorTakesPatients( howManyPatientsAtOnce, numOfDocs, heap, patientCount,
                         serviceTimes, timePast, returnStr);
        int minServiceTime = INT_MAX;
        int i;
        for( i = 0; i < numOfDocs; i++) {
            if( serviceTimes[i] == 0) break;
            if( serviceTimes[i] < minServiceTime) {
                minServiceTime = serviceTimes[i];
            }
        }
        if( i != numOfDocs && serviceTimes[i] == 0) {
            timePast = tempPat.getArrivalTime();
            minServiceTime = tempPat.getArrivalTime() - timePast;
        }
        else timePast += minServiceTime;

        for( int i = 0; i < numOfDocs; i++) {
            serviceTimes[i] = serviceTimes[i] - minServiceTime; //some may go to 0 at this point
        }

        if( avgWait > maxWait * patCountOverall) { //if average waiting time exceeds what we want to achieve
            return "";              //we immediately go back
        }
    }
    avgWait = avgWait / patCountOverall;
    return returnStr;
}

int main( int argc, const char * argv[]) {
    argc = 3; //programname-fileName-maxWait
    //Heap works properly
    Heap heap1;
    string fileName;
    int maxWait;
    fileName = argv[1];

    string temp = argv[2];
    istringstream( temp) >> maxWait;    
    int numDoc = 1;
    double avgWait = 0;

    string runResult = run( fileName.c_str(), heap1, numDoc, maxWait, avgWait); //first try it with 1 doctor

    bool successful = ( runResult.length() > 0); //if this is not successful, it will return an empty string
    while( !successful) {
        avgWait    = 0; //reset to its original state
        numDoc++;
        runResult  = run( fileName.c_str(), heap1, numDoc, maxWait, avgWait);
        successful = ( runResult.length() > 0);
    }

    if( avgWait > -1) cout<<"\nMinimum number of doctors required: "<<numDoc<<"\nSimulation with "<<numDoc<<" doctors:\n\n";
    cout<<runResult;
    if( avgWait > -1) printf("Average waiting time: %.2f", avgWait);

    return 0;
}
