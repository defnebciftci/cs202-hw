/**
* Author: Defne Betül Çiftci
* ID: 21802635
* Section: 2
* Assignment: 2
*/
#ifndef DECISIONTREENODE_H_INCLUDED
#define DECISIONTREENODE_H_INCLUDED
//the class keeps track of whether or not the node is a
//leaf node, the feature index for its decision (split)
//if it is a non-leaf node, its class decision if it is a
//leaf node, and pointers to its children
//data members and functions are up to us
using namespace std;

struct DecisionTreeNode {
public:
    DecisionTreeNode();
    void setData( const bool*& featureArray, const int numSamples);
    const bool isLeaf();
    const bool setAsLeaf( const int label);
    const int getFeatureIndex();
    void setFeatureIndex( const int index);
    const int getLabelData();
    DecisionTreeNode* leftChild  ;
    DecisionTreeNode* rightChild ;

private:
    const int INIT_SIZE = 10;
    int featureIndex;
    bool* data; //holds a feature array, will need an increment size function later
    int labelData;
    bool pure;

    void incrementSize( const int); //for data array
};

#endif // DECISIONTREENODE_H_INCLUDED
