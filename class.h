#ifndef CLASS_H
#define CLASS_H

using namespace std;
class DataSet{
private:
	void WrongData();
public:
	int nFeatures;
	vector<int> featureTable;
	vector<vector<float>> data;
	DataSet(char* fileName);
};


#endif
