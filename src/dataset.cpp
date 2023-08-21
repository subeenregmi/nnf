#include "dataset.hpp"

void Dataset::allocate(){

	int testrows = Data->rows * (1 - Percentage); 
	std::set<int> training;
	std::set<int> test;

	for(int i=1; i<=Data->rows; i++){
		training.insert(i);
	}

	while(test.size() != testrows){
		int r = rand() % Data->rows;
		if(training.find(r) != training.end()){
			test.insert(r);
			training.erase(r);
		}
	}

	TrainingData = new Matrix(training.size(), Data->cols);	
	if(test.size() == 0){
		TestData = new Matrix(training.size(), Data->cols);
	}
	else{
		TestData = new Matrix(test.size(), Data->cols);
	}

	int i = 1;
	for(int r : training){
		TrainingData->copyrow(Data, r, i);
		i++;
	}
	i=1; 
	for(int r : test){
		TestData->copyrow(Data, r, i);
		i++;
	}
}

Dataset::Dataset(Matrix* data, dataT percent){	
	int trainingrows = data->rows * percent;
	assert(trainingrows > 0);
	Percentage = percent;
	Data = data;
	allocate();
}

Dataset::~Dataset(){
	if(TrainingData != nullptr){
		delete(TrainingData);
	}
	if(TestData != nullptr){
		delete(TestData);
	}
}
