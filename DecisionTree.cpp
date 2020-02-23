#include<iostream>
#include<fstream>
#include<vector>
#include "class.h"
//#include<typeinfo>
using namespace std;

int main(int argc, char *argv[])
{
	DataSet* trainingSet = new DataSet(argv[1]);
	
	for (int i = 0; i < trainingSet->data.size(); ++i){
		for (int j = 0; j < trainingSet->nFeatures; ++j){
			cout << trainingSet->data[i][j] << " ";
		}
		cout << endl;
	}

	return 1;
}
