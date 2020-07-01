/**
* Author: Defne Betül Çiftci
* ID: 21802635
* Section: 2
* Assignment: 2
*/
#ifndef DECISIONTREE_H_INCLUDED
#define DECISIONTREE_H_INCLUDED
#include "DecisionTreeNode.h"
#include <string>
//the class should keep a pointer to the root
double calculateInformationGain( const bool** data, const int* labels,const int numSamples,
                                const int numFeatures, bool* usedSamples,const int featureId);
void countClasses( const int numSamples,
                  int*& classCountsAll, int& numClassesAll, const int*& labels , //these are for the parent
                  int*& countClass0, int& count0, //this is for the left child, aka for values that are 0
                  int*& countClass1, int& count1,
                  bool* columnWithFeature, //we will retrieve the information for 0 and 1 from this
                  const bool* usedSamples
                  ) ;
void deallocateIntArray( int* arr, const int size);
double calculateEntropy(const int* classCounts, const int numClasses);
void incrementSize( int*& arr, int size);

const int LOGBASE = 2;
const int INITIAL_SIZE = 5;

using namespace std;
class DecisionTree {
public:
    void train(const bool**, const int*, const int, const int);
    void train(const string, const int, const int);
    int predict(const bool*);
    double test(const bool**, const int*, const int);
    double test(const string, const int);
    void print();
private:
    const bool** turnFileIntoArray( const string fileName, int*& labels, const int numSamples);
    DecisionTreeNode* decideOnRoot( bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples,
                                             bool* parentNodes);
    void printPreorder( DecisionTreeNode* node, int numOfTabs);
    DecisionTreeNode* root;

    int numFeatures = -1;
};


#endif // DECISIONTREE_H_INCLUDED

