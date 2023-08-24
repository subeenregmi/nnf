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
		if(test.size() == 0){
			TestData->copyrow(Data, r, i);
		}
		i++;
	}
	i=1; 
	for(int r : test){
		TestData->copyrow(Data, r, i);
		i++;
	}
}

void Dataset::getTrainingExample(int r, Matrix* x, Matrix* y){
	assert(x->rows == Inputs);
	assert(y->rows == Outputs);
	assert((x->cols == 1) && (y->cols == 1));
	assert((r >= 0) && (r < TrainingData->rows));
	
	//copying values into x
	for(int i=0; i<Inputs; i++){
		(*x)[i][0] = (*TrainingData)[r][i];
	}
	// copying values into y
	for(int i=0; i<Outputs; i++){
		(*y)[i][0] = (*TrainingData)[r][Inputs + i];
	}
}

void Dataset::getTestExample(int r, Matrix* x, Matrix* y){
	assert(x->rows == Inputs);
	assert(y->rows == Outputs);
	assert((x->cols == 1) && (y->cols == 1));
	assert((r >= 0) && (r < TrainingData->rows));
	
	//copying values into x
	for(int i=0; i<Inputs; i++){
		(*x)[i][0] = (*TestData)[r][i];
	}
	// copying values into y
	for(int i=0; i<Outputs; i++){
		(*y)[i][0] = (*TestData)[r][Inputs + i];
	}
}

Dataset::Dataset(Matrix* data, dataT percent, int input){	
	assert((data->rows * percent) > 0);
	assert(input < data->cols);

	Percentage = percent;
	Data = data;
	Inputs = input;
	Outputs = data->cols - input;
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
