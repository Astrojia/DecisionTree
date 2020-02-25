#ifndef CLASS_H
#define CLASS_H

using namespace std;

class DataSet{	//Data structure used to save data sets.
private:
	void WrongData();	//Error report when data is wrong.
public:
	int nFeatures;	//How many features a data sets have(including label).
	vector<int> featureTable;	//How many types in each feature, 0 represents continuous features.
	vector<vector<float>> data;	//Data set.

	DataSet(char* fileName);	//Constructor.
};

vector<int> BuildFeatureFlag(int num);

class Node{
public:
	int featureIndex;	//Which feature this node represents.
	bool isLeaf;	//Is that node a leaf node.
	vector<Node*> nodes;	//Children nodes of current node.

	Node(int index, bool leafSign);	//Constructor.
};

class DecisionTree{
private:
	Node* root;
	int FindMostEntropyIncreaseIndex(DataSet& dataset, vector<int>& featureUsedFlag, float& dividingPoint);
	vector<float> EntropyIncreaseCalculator(DataSet& dataSet, vector<int>& featureUsedFlag, float& dividingPoint);
	float Entropy(DataSet& dataSet, int index);
	
public:
	DecisionTree(DataSet& dataSet, vector<int> featureUsedFlag);
};
#endif
