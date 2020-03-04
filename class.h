#ifndef CLASS_H
#define CLASS_H

using namespace std;

class DataSet{	//Data structure used to save data sets.
private:
	void WrongData();	//Error report when data is wrong.
public:
	int nFeatures;	//How many features a data sets have(including label).
	vector<int> featureTable;	//How many types in each feature, 0 represents continuous features. -1 represents feature have already used.
	vector<vector<float>> data;	//Data set.

	DataSet(char* fileName);	//Constructor.
	DataSet();
};

class Node{
public:
	int featureIndex;	//Which feature this node represents.
	bool isLeaf;	//Is that node a leaf node.
	float dividingPoint;	//Prepare for continuous feature.
	vector<Node*> nodes;	//Children nodes of current node.

	Node();
	Node(int index, bool leafSign);	//Constructor.
	Node(int index, bool leafSign, float dividingPoint);	//Constructor for continuous feature. The compiler will not generate a default constructor in the presence of other constructors.
};

class DecisionTree{
private:
	bool SameType(DataSet& dataSet);
	bool AllFeatureUsed(DataSet& dataSet);
	bool SameFeatures(DataSet& dataSet);
	int MostCommonType(DataSet& dataSet);
	int FindMostEntropyIncreaseIndex(DataSet& dataset, float& dividingPoint);
	float FeatureEntropyForContinuous(DataSet& dataSet, int index, float& dividingPoint);
	vector<DataSet> SubSetMakerForContinuous(DataSet& dataSet, int index, float dividingPoint);
	float FeatureEntropy(DataSet& dataSet, int index);
	vector<DataSet> SubSetMaker(DataSet& dataSet, int index, bool useFeature = false);	//Subset maker for index th feature. useFeature = false when calculate gain, useFeature = true when generate son nodes.
	float Entropy(DataSet& dataSet);
public:
	Node* root;

	DecisionTree(DataSet& dataSet);

	void PrintTreeStructure(Node* node, vector<int>& featureTable);
};
#endif
