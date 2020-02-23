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
