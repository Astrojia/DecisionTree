#include<iostream>
#include<vector>

using namespace std;

float Tree::Entropy(DataSet& dataSet, int index){
        float entropy = 0;
        nSamples = dataSet.data.size();
        vector<int> typeCount(featureTable[index])
        for int(i = 0; i < nSamples; ++i)
                typeCount[dataSet.data[index]]++
