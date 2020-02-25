#include<iostream>
#include<fstream>
#include<vector>
#include<string>
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

vector<int> BuildFeatureFlag(int num){
	vector<int> flags;
 	for(int i = 0; i < num; ++i)
		flags.push_back(0);
	return flags;
}

Node::Node(int index, bool leafSign):featureIndex(index),isLeaf(leafSign){}

DecisionTree::DecisionTree(DataSet& dataSet, vector<int> featureUsedFlag){
	float dividingPoint = 0;
	int featureIndex = FindMostEntropyIncreaseIndex(dataSet, featureUsedFlag, dividingPoint);
}

int DecisionTree::FindMostEntropyIncreaseIndex(DataSet& dataSet, vector<int>& featureUsedFlag, float& dividingPoint){
	cout << "Enter FindMostEntroppyIncreaseIndex" << endl;
	vector<float> entropyIncreaseList;
	entropyIncreaseList = EntropyIncreaseCalculator(dataSet, featureUsedFlag, dividingPoint);
	int index;
	return index;
}


vector<float> DecisionTree::EntropyIncreaseCalculator(DataSet& dataSet, vector<int>& featureUsedFlag, float& dividingPoint){
	cout << "Enter EntropyIncreaseCalculator" << endl;
	float entropy = Entropy(dataSet,dataSet.nFeatures-1);
	vector<float> entropyIncreaseList;
//	for(int i = 0; i < dataSet.NFeatures; ++i)
	return entropyIncreaseList;
}

float DecisionTree::Entropy(DataSet& dataSet, int index){
	cout << "Enter Entroppy" << endl;
	float entropy = 0;
	int nSamples = dataSet.data.size(); 
	vector<int> typeCount(dataSet.featureTable[index]);
	for (int i = 0; i < nSamples; ++i)
		typeCount[dataSet.data[i][index]]++;
	return entropy;
}
