#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include "class.h"

using namespace std;

void DataSet::WrongData(){
	cout << "Data Error" << endl;
}

DataSet::DataSet(char* fileName){
	ifstream input(fileName);
	if (!input){
		WrongData();
		input.close();
	}
	input >> nFeatures;
	for(int i = 0; i < nFeatures; ++i){
		int  temp;
		input >> temp;
		featureTable.push_back(temp);
	}
	while(!input.eof()){
		vector<float> temp_vector;
		float temp;
		for(int i = 0; i < nFeatures; ++i){
			if (input >> temp){
				temp_vector.push_back(temp);
				if (i == nFeatures-1) data.push_back(temp_vector);
			}
		}
	}
	input.close();
}

DataSet::DataSet(){}

Node::Node(){
	featureIndex = -1;
	isLeaf = false;
}

Node::Node(int index, bool leafSign):featureIndex(index),isLeaf(leafSign){}

Node::Node(int index, bool leafSign, float dividingPoint):featureIndex(index), isLeaf(leafSign), dividingPoint(dividingPoint){}

DecisionTree::DecisionTree(DataSet& dataSet){
	cout << "Biulding tree for " << dataSet.data.size() << "samples" << endl;
	root = new Node();
	if(SameType(dataSet)){	//All data belong to same type.
		root->isLeaf = true;
		root->featureIndex = dataSet.data[0][dataSet.nFeatures - 1];
		return;
	}
	if(AllFeatureUsed(dataSet) || SameFeatures(dataSet)){	//All feature have used or all data have same features.
		root->isLeaf = true;
		root->featureIndex = MostCommonType(dataSet);
	}
	float dividingPoint = 0;	//Prepare for continuous feature.
	int featureIndex = FindMostEntropyIncreaseIndex(dataSet, dividingPoint);	//Finding optimal partitionig feature.
	cout << "Feature with most gain is " << featureIndex << endl;
	vector<DataSet> subSets;
	if(dataSet.featureTable[featureIndex] != 0){
		root->featureIndex = featureIndex;
		subSets = SubSetMaker(dataSet, featureIndex, true);
	}
	else{
		root->featureIndex = featureIndex;
		root->dividingPoint = dividingPoint;
		subSets = SubSetMakerForContinuous(dataSet, featureIndex, dividingPoint);
	}
	for(int i = 0; i < subSets.size(); i++){
		if(subSets[i].data.size() == 0)
			root->nodes.push_back(new Node(MostCommonType(dataSet), true));
		else{
			DecisionTree* subTree = new DecisionTree(subSets[i]);
			root->nodes.push_back(subTree->root);
		}	
	}
}

bool DecisionTree::SameType(DataSet& dataSet){
	for(int i = 0; i < dataSet.data.size() - 1; ++i){
		if(dataSet.data[i][dataSet.nFeatures - 1] != dataSet.data[i+1][dataSet.nFeatures - 1])
			return false;
	}
	return true;
}

bool DecisionTree::AllFeatureUsed(DataSet& dataSet){
	for(int i = 0; i < dataSet.nFeatures-1; ++i){
		if(dataSet.featureTable[i] != -1)
			return false;
	}
	return true;
}

bool DecisionTree::SameFeatures(DataSet& dataSet){
	for(int i = 0; i < dataSet.data.size() - 1; ++i){
		for(int j = 0; j < dataSet.nFeatures - 1; ++j){
			if(dataSet.data[i][j] != dataSet.data[i+1][j])
				return false;
		}
	}
	return true;
}

int DecisionTree::MostCommonType(DataSet& dataSet){
	int type = -1;
	int maxCount;
	vector<int> typeCount(dataSet.featureTable[dataSet.nFeatures - 1]);
	for(int i = 0; i < dataSet.data.size(); ++i)
		typeCount[dataSet.data[i][dataSet.nFeatures-1]]++;
	for(int i = 0; i < dataSet.featureTable[dataSet.nFeatures - 1]; ++i){
		if(typeCount[i] > maxCount){
			maxCount = typeCount[i];
			type = i;
		}
	}
	if(type == -1)
		cout << "Wrong most common type!" << endl;
	return type;
}

int DecisionTree::FindMostEntropyIncreaseIndex(DataSet& dataSet, float& dividingPoint){
//	cout << "Enter FindMostEntroppyIncreaseIndex" << endl;
	int index = dataSet.nFeatures-1;
	float dataEntropy = Entropy(dataSet);
//	cout << "Set Entropy = " << dataEntropy << endl; 
	float maxGain = 0;
	for(int i = 0; i < dataSet.nFeatures-1; ++i){
		cout << "max Gain = " << maxGain << endl;
		if(dataSet.featureTable[i] == -1) continue;
		else if(dataSet.featureTable[i] == 0){
			float currentDividingPoint;
			float currentGain = dataEntropy - FeatureEntropyForContinuous(dataSet, i, currentDividingPoint);
			cout << "Gain for feature " << i << " = " << currentGain << endl;
			if(currentGain > maxGain){
				maxGain = currentGain;
				index = i;
				dividingPoint = currentDividingPoint;
			}
		}
		else{
			float currentGain = dataEntropy -  FeatureEntropy(dataSet, i);
			cout << "Gain for feature " << i << " = " << currentGain << endl;
			if(currentGain > maxGain){
				maxGain = currentGain;
				index = i;
			}
		}
	}
	return index;
}


float DecisionTree::FeatureEntropyForContinuous(DataSet& dataSet, int index, float& dividingPoint){	//TBF
	float entropy = Entropy(dataSet) + 1;
	vector<float> dividingCand;	//Biuld an vector dividingCand to store candidate dividing point.
	vector<float> valueList;
	for(int i = 0; i < dataSet.data.size(); ++i)
		valueList.push_back(dataSet.data[i][index]);
	sort(valueList.begin(),valueList.end());	//Sort the feature[index] value
	for(int i = 0; i < valueList.size()-1; ++i){	//Find all candidate for dividingPoint store in a vector<float>
		if(valueList[i] != valueList[i+1])
			dividingCand.push_back((valueList[i] + valueList[i+1]) / 2);
	}
	vector<float> entropyList(dividingCand.size()); // Biuld an vector to store entropy.
	for(int i = 0; i < dividingCand.size(); ++i){	//Make subsets and calculate their entropy for each dividingPoint, store it in entropyList
		vector<DataSet> subSets = SubSetMakerForContinuous(dataSet, index, dividingCand[i]);
		for(int j = 0; j < subSets.size(); ++j)
			entropyList[i] += float(subSets[j].data.size()) / float(dataSet.data.size()) * Entropy(subSets[j]);
	}
	for(int i = 0; i < dividingCand.size(); ++i){	//Find the min in entropyList and give the value to entropy, give the corresponding value to dividingPoint.
		if(entropyList[i] < entropy){
			entropy = entropyList[i];
			dividingPoint = dividingCand[i];
		}
	}
	return entropy;
}	

vector<DataSet> DecisionTree::SubSetMakerForContinuous(DataSet& dataSet, int index, float dividingPoint){	//TBF Not add to class.h
//	cout << "Enter SubSetMakerForContinuous" << endl;
	vector<DataSet> subSets(2);
	for(int i = 0; i < 2; ++i){
		subSets[i].nFeatures = dataSet.nFeatures;
		subSets[i].featureTable = dataSet.featureTable;
	}
	for(int i = 0; i < dataSet.data.size(); ++i){
		if (dataSet.data[i][index] <= dividingPoint)
			subSets[0].data.push_back(dataSet.data[i]);
		else
			subSets[1].data.push_back(dataSet.data[i]);
	}
	return subSets;
}

float DecisionTree::FeatureEntropy(DataSet& dataSet, int index){
	float entropy;
	vector<DataSet> subSets;
	subSets = SubSetMaker(dataSet, index);
	for(int i = 0; i < dataSet.featureTable[index]; ++i)
		entropy += float(subSets[i].data.size()) / float(dataSet.data.size()) * Entropy(subSets[i]);	//calculate feature entropy
	return entropy;
}	

vector<DataSet> DecisionTree::SubSetMaker(DataSet& dataSet, int index, bool useFeature){	//Default velue for useFeature is false.
//	cout << "Enter SubSetMaker" << endl;
	vector<DataSet> subSets(dataSet.featureTable[index]);
	vector<int> newFeatureTable = dataSet.featureTable;	//Set feature 
	if(useFeature)
		newFeatureTable[index] = -1;
	for(int i = 0; i < dataSet.featureTable[index]; ++i){
		subSets[i].nFeatures = dataSet.nFeatures;
		subSets[i].featureTable = newFeatureTable;
	}
	for(int i = 0; i < dataSet.data.size(); ++i)
		subSets[dataSet.data[i][index]].data.push_back(dataSet.data[i]);
	return subSets;
}


float DecisionTree::Entropy(DataSet& dataSet){
//	cout << "Enter Entroppy" << endl;
	float entropy = 0;
	int nSamples = dataSet.data.size(); 
	vector<float> typeCount(dataSet.featureTable[dataSet.nFeatures-1]);
	for (int i = 0; i < nSamples; ++i)
		typeCount[dataSet.data[i][dataSet.nFeatures-1]]++;
	for (int i = 0; i < dataSet.featureTable[dataSet.nFeatures-1]; ++i){
		if(typeCount[i] > 0)
			entropy -= typeCount[i]/float(nSamples) * log2(typeCount[i]/float(nSamples));
	}
	return entropy;
}

void DecisionTree::PrintTreeStructure(Node* node, vector<int>& featureTable){
	if (node->isLeaf){
		cout << "Is type " << node->featureIndex << endl;
		return;
	}
	cout << "Feature " << node->featureIndex << "on this node" << endl;
	if (featureTable[node->featureIndex] == 0)
		cout << "dividingPoint is " << node->dividingPoint << endl;
	for (int i = 0; i < node->nodes.size(); ++i)
		PrintTreeStructure(node->nodes[i], featureTable);
	return;
}

