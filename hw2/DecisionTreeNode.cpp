/**
* Author: Defne Betül Çiftci
* ID: 21802635
* Section: 2
* Assignment: 2
*/
#include "DecisionTreeNode.h"
#include <iostream>
using namespace std;

DecisionTreeNode::DecisionTreeNode() : labelData( -1), data( NULL), featureIndex( -1),
                                        pure( false) {
}

void DecisionTreeNode::setData( const bool*& featureArray, const int numSamples) {
    //data = featureArray; //shallow copy
    data = new bool[ numSamples];
    for( int i = 0; featureArray != NULL && i < numSamples; i++) {
        data[i] = featureArray[i];
    } //deep copy
}
/**
*checks if the featureArray to be analized is pure and if it is pure,
*changes the labelData accordingly
*/
const bool DecisionTreeNode::setAsLeaf( const int label) {
    rightChild = NULL;
    leftChild  = NULL;
    labelData  = label;
}

const bool DecisionTreeNode::isLeaf() {
    return ( rightChild == NULL && leftChild == NULL);
}
/**
*returns the feature index of the node
*/
const int DecisionTreeNode::getFeatureIndex() {
    return featureIndex;
}

/**
*sets featureIndex to index in the parameters
*/
void DecisionTreeNode::setFeatureIndex( const int index) {
    featureIndex = index;
}

const int DecisionTreeNode::getLabelData() {
    return labelData;
}

//void setAsLeaf() {
//    rightChild = NULL;
//    leftChild = NULL;
//}
//bool isLeaf() {
//    return ( rightChild == NULL && leftChild == NULL);
//}

//bool isPure() {
//    if( data == NULL) return true;
//}

