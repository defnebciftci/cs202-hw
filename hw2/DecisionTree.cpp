/**
* Author: Defne Betül Çiftci
* ID: 21802635
* Section: 2
* Assignment: 2
*/

#include "DecisionTree.h"
#include "DecisionTreeNode.h"
#include <iostream> //for cout
#include <fstream> //for ifstream
#include <bits/stdc++.h> //to import the log() function
#include <limits> //for the INT_MIN value
using namespace std;

//first the global functions, then class ones
double calculateEntropy(const int* classCounts, const int numClasses) {
    double entropy = 0;
    double sum     = 0;
    double eachCalculation; //this will change for each value of classCounts
    for( int i = 0; i < numClasses; i++) {
        sum += classCounts[ i];
    } //we will use the sum for dividing each class count
    for( int i = 0; i < numClasses; i++) {
        if( classCounts[ i] != 0) {
            eachCalculation = ( ((double) classCounts[ i] )/ sum);
            eachCalculation *= ( log( ( ((double) classCounts[ i]) / sum)) / log( LOGBASE ));
            entropy += eachCalculation; //will increment by each of these calculations
        }
    }
    if( entropy != 0)   entropy *= (-1); //we don't want to create a -0.000
    return entropy;
}
void deallocateIntArray( int* arr, const int size) {
    for( int i = 0; i < size; i++)
        arr[i] = NULL;
    delete[] arr;
}

void countClasses( const int numSamples,
                  int*& classCountsAll, int& numClassesAll, const int*& labels , //these are for the parent
                  int*& countClass0, int& count0, //this is for the left child, aka for values that are 0
                  int*& countClass1, int& count1,
                  bool* columnWithFeature, //we will retrieve the information for 0 and 1 from this
                  const bool* usedSamples
                  ) {
    int* newLabels = new int[10]; //this will hold the values for each label so if we come across a label that
                                  //we already saw, we can increment classCountsAll as usual
    bool found;

    int sizeAll, size0, size1 = INITIAL_SIZE;
    //initializing the values first for the isPure boolean
    newLabels[ 0] = labels[ 0];
    classCountsAll[ 0] = 1;
    if( columnWithFeature[ 0] == 0) {
        countClass0[ 0] = 1;
        count0++;
    }
    else if( columnWithFeature[ 0] == 1) { //there  is no other possibility, but just in case
        countClass1[ 0] = 1;
        count1++;
    }
    numClassesAll++;

    for( int i = 1; i < numSamples; i++) {
        found = false; //this will help to recognize if there is a new label or if a label is repeated
                       // we only consider the ones where usedSamples is true
        //below is for reallocating arrays to bigger sized arrays if necessary
        if( numClassesAll > sizeAll) incrementSize( classCountsAll, sizeAll);
        if( count0 > size0)          incrementSize( countClass0, size0);
        if( count1 > size1)          incrementSize( countClass1, size1);

        for( int j = 0; j < numClassesAll && !found; j++) { //loop will go around each label in newLabels
            if( newLabels[j] == labels[i] && usedSamples[i]) {
                classCountsAll[ j]++; //new labels are added in the same order with classCountsAll
                found = true; //so that we dont waste too much time going through each newLabel
                if( !columnWithFeature[ i]) {
                    countClass0[ j]++;
                    count0++;
                }
                else if( columnWithFeature[ i] == 1) { //there  is no other possibility, but just in case
                    countClass1[ j]++;
                    count1++;
                }
            }
        }
        if( !found && usedSamples[i]) { //this means that the label is a new one, so we add it to newLabels
            newLabels[ numClassesAll] = labels[ i];
            classCountsAll[ numClassesAll] = 1;
            if( columnWithFeature[ i] == 0) {
                countClass0[ numClassesAll] = 1;
                count0++;
            }
            else if( columnWithFeature[ i] == 1) { //there  is no other possibility, but just in case
                countClass1[ numClassesAll] = 1;
                count1++;
            }
            numClassesAll++;
        }
    }
}
/**
for calculateInformationGain
*/
void incrementSize( int*& arr, int size) {
    int* temp = new int[size*2];
    //copy the old ones to temp
    for( int i = 0; i < size; i++) { //size is the old size
        temp[i] = arr[i];
    }
    size *= 2;//increase size
    delete[] arr;//free old memory
    arr = temp;
}
double calculateInformationGain( const bool** data, const int* labels,const int numSamples,
                                const int numFeatures, bool* usedSamples,const int featureId) {
    if( data == NULL )  return 0; //return if there is no data available

    //int maxInfoGain = INT_MIN; //will use at some point
    int* classCountsAll = new int[INITIAL_SIZE]; //An initial size, will increment if needed, all values are 0 initially
    for( int i = 0; i < INITIAL_SIZE; i++) { //initialize as 0
        classCountsAll[i] = 0;
    }
    int numClassesAll  = 0; //we will count the classes using the labels class of size numSamples

    int* countClass0   = new int[INITIAL_SIZE]; //An initial size, will increment if needed, all values are 0 initially
    for( int i = 0; i < INITIAL_SIZE; i++) { //initialize as 0
        countClass0[i] = 0;
    }
    int count0         = 0;

    int* countClass1   = new int[INITIAL_SIZE]; //An initial size, will increment if needed, all values are 0 initially
    for( int i = 0; i < INITIAL_SIZE; i++) { //initialize as 0
        countClass1[i] = 0;
    }
    int count1         = 0;

    bool* columnWithFeature = new bool[ numSamples];
    for( int i = 0; i < numSamples; i++) { columnWithFeature[i] = data[i][ featureId]; //get the column values aka values for feature
    }

    countClasses(  numSamples,
                classCountsAll, numClassesAll, labels, //these are for the parent
                countClass0, count0, //this is for the left child, aka for values that are 0
                countClass1, count1, //for right child
                columnWithFeature, //we will retrieve the information for 0 and 1 from this
                usedSamples );
    double parentEntropy = calculateEntropy( classCountsAll, numClassesAll); //calculate parent entropy
    double childEntropy  = calculateEntropy( countClass0, numClassesAll) * count0 / numSamples; //this is for the left child
    childEntropy        += calculateEntropy( countClass1, numClassesAll) * count1 / numSamples; //add the right child

    delete[]               classCountsAll;
    classCountsAll       = NULL;
    delete[]               countClass1;
    countClass0          = NULL;
    delete[]               countClass0;
    countClass1          = NULL;
    return               ( parentEntropy - childEntropy) ; //return their difference to get information gain
}

DecisionTreeNode* DecisionTree::decideOnRoot( bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples,
                                             bool* parentNodes) {
//usedSamples ekle, zeroData ve oneDatayý sil, getLesserý sil
    DecisionTreeNode* node = new DecisionTreeNode();
    double max = INT_MIN; //initialize max as the minimum number possible
    double temp = 0;
    int featureIndex = 0;

    for( int i = 0; i < numFeatures; i++) {
        temp = calculateInformationGain( (const bool**) data, labels, numSamples, numFeatures, (bool*) usedSamples, i);
        if( temp > max && !parentNodes[i]) {
            featureIndex = i; //this will hold the index we need
            max = temp; //we change max to check on the maximum information gain every time a bigger info gain shows up
        }
    } //featureIndex is the index with the biggest information gain now

    bool isPure = true;
    int label = -1;
    int i;
    for( i = 0; i < numSamples; i++) {
        if(usedSamples[i]) {
            label = labels[i];
            break;
        }
    }
    for( ; i < numSamples; i++) {
        if( usedSamples[i] && labels[i] != label) {
            isPure = false;
            break;
        }
    }
    if( isPure && label != -1) {
        node->setAsLeaf( label); //this will also assign the labelData
        return node;
    }
    node->setFeatureIndex( featureIndex);//and set its index to the specified node

    parentNodes[ featureIndex] = true;

    bool* rootData = new bool[numSamples];
    for( int i = 0; i < numSamples; i++) {
        rootData[i] = data[i][featureIndex];
    }

    bool* usedSamples0 = new bool[numSamples];
    bool* usedSamples1 = new bool[numSamples];
    for( int i = 0; i < numSamples; i++) {
        if( rootData[i] == false && usedSamples[i]) {
            usedSamples0[i] = true;
            usedSamples1[i] = false;
        }
        else if( rootData[i] == true && usedSamples[i]) { //rootData[i] == 1 then
            usedSamples0[i] = false;
            usedSamples1[i] = true;
        }
        else {
            usedSamples0[i] = false;
            usedSamples1[i] = false;
        }
    }

    node->leftChild = decideOnRoot( data, (const int*) labels, numSamples, numFeatures, usedSamples0, parentNodes);//recursive for training

    //do the same for 1's
    node->rightChild = decideOnRoot( data, (const int*) labels, numSamples, numFeatures, usedSamples1, parentNodes );

    return node;
}
void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures) {
    this->numFeatures = numFeatures;
   //used samples array here, in which everything is true
    bool* usedSamples = new bool[numSamples];
    bool* parentNodes = new bool[numFeatures];
    for( int i = 0; i < numSamples; i++) {
        usedSamples[i] = true;
    }
    for( int i = 0; i < numFeatures; i++)
        parentNodes[i] = false;
    //int index = 0;
    //int prevFeatIndex = -1;
    root = decideOnRoot( (bool**) data, labels, numSamples, numFeatures, usedSamples, parentNodes);

    delete[] usedSamples;
    usedSamples = NULL;
}

int DecisionTree::predict(const bool* data) {
    if( numFeatures == -1)      return -1; //this means that train function has never been visited
    //after train function
    DecisionTreeNode* current = root;
    int               index;
    while( !current->isLeaf()) {
        index = current->getFeatureIndex();
        if( data[index] == 0) current = current->leftChild;
        else                  current = current->rightChild;
    }
    return current->getLabelData();
}

void DecisionTree::train(const string fileName, const int numSamples,const int numFeatures) {
    int* labels;
    const bool** data;

    data = turnFileIntoArray( fileName, labels, numSamples);
    train( data, labels, numSamples, numFeatures);
}
double DecisionTree::test(const bool** data, const int* labels, const int numSamples) {
    int guess;
    double countTrue = 0;
    for( int i = 0 ; i < numSamples; i++) {
        guess = predict( data[i]);
        if( guess == labels[i]) countTrue++;
    }
    return (countTrue / numSamples);
}
double DecisionTree::test(const string fileName, const int numSamples) {
    int* labels;
    const bool** data;
    data = turnFileIntoArray( fileName, labels, numSamples);
    return test( (const bool**) data, (const int*) labels, numSamples); //use the actual test function
}
void DecisionTree::print() {
    DecisionTreeNode* curr = root;
    printPreorder( curr, 0);
}
void DecisionTree::printPreorder( DecisionTreeNode* node, int numOfTabs) {
    if( node->getLabelData() != -1) {
        for( int i = 0; i < numOfTabs; i++) cout<<"\t";
        cout<<"class= "<<node->getLabelData()<<endl;
        return;
    }
    for( int i = 0; i < numOfTabs; i++) cout<<"\t";
    cout<<"FeatureId= "<<node->getFeatureIndex()<<endl;
    printPreorder( node->leftChild,  numOfTabs++);
    printPreorder( node->rightChild, numOfTabs++);
}
/**
*returns labels array and data mulitdimensional array by reference
*/
const bool** DecisionTree::turnFileIntoArray( const string fileName, int*& labels, const int numSamples) {
    string line;
    ifstream file (fileName.c_str());

    bool* sampleArr = 0; //init as NULL
    labels = new int[numSamples]; //init labels
    bool** data = new bool*[numSamples]; //init the first dimension of data array
    numFeatures = 0;
    int indexSample = 0;

    if( !file.is_open()) cout<<"cannot open file"<<endl; //just in case
    else {
        while( getline( file, line)) {
            //first we handle each line as a string, removing the spaces
            for( int i = 0; i < line.length(); i++) {
                if( line[i] == ' ') { //this is to see if they are equal
                    line = line.substr( 0, i) + line.substr( i + 1, (line.length() - i ));
                    i--;
                }
            }
            sampleArr = new bool[line.length() - 1];
            if( numFeatures != line.length() - 1) { //this is before we know the numFeatures, so we initialize it first
                numFeatures = line.length() - 1;
                for( int i = 0; i < numSamples; i++) {
                    data[i] = new bool[numFeatures]; //we initialize the whole array as well, now that we know numFeatures
                }
            }
            for( int i = 0; i < line.length() - 1; i++) {//we put bool values inside each array for each sample
                bool b;
                if( line[i] == '0') b = false;
                else                b = true;
                sampleArr[i] = b;
            }
            labels[ indexSample]   = (int) (line[line.length() - 1]) - 48; //we first get the ascii char, so we subtract 48 to get the int
            data[ indexSample] = sampleArr;
            //indexSample is there to put the labels in their proper order as well as each sample array
            indexSample++;
        }
    }
    //to free up memory space
    delete[] sampleArr;
    sampleArr = NULL;
    return (const bool**) data;
}

int main() {
    DecisionTree tree1;
//    DecisionTree tree2;
    int numSamples = 499;
    int numFeatures = 21;
    tree1.train( "asd.txt", numSamples, numFeatures);
    cout<<"train successfulaa"<<endl;
    tree1.print();
    cout<<"test: "<<tree1.test( "asd.txt", numSamples)<<endl;
//    cout<<"----TREE 2----"<<endl;
//    tree2.train( "train_data.txt", numSamples, numFeatures);
//    cout<<"check2"<<endl;
////
    bool data[21] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
    bool* dataPtr = new bool[21];
    dataPtr = data;
    cout<<"predict: "<<tree1.predict( (const bool*) dataPtr)<<endl;
//    cout<<"test: "<<tree2.test( "asd.txt", 249)<<endl;
//    tree2.print();
    //tree.print();
    return 0;
}



