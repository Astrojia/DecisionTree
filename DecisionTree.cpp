#include<iostream>
#include<vector>
#include "class.h"
//#include<typeinfo>
using namespace std;

int main(int argc, char *argv[])
{
	DataSet* trainingSet = new DataSet(argv[1]);
	DecisionTree* tree = new DecisionTree(*trainingSet);
	cout << "Build Tree Done" << endl;
	tree->PrintTreeStructure(tree->root, trainingSet->featureTable);
	return 1;
}
