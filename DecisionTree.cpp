#include<iostream>
#include<fstream>
#include<vector>
#include "class.h"
//#include<typeinfo>
using namespace std;

int main(int argc, char *argv[])
{
	DataSet* trainingSet = new DataSet(argv[1]);
	vector<int> featureUsedFlag = BuildFeatureFlag(trainingSet->nFeatures);	//Feature have used
	DecisionTree* tree = new DecisionTree(*trainingSet, featureUsedFlag);

	return 1;
}
