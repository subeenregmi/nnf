#include "dataset.hpp"

void Dataset::getTrainingExample(int r, Matrix* x, Matrix* y){
	assert(x->rows == Inputs);
	assert(y->rows == Outputs);
	assert((x->cols == 1) && (y->cols == 1));
	assert((r >= 0) && (r < TrainingData->rows));
	
	//copying values into x
	for(int i=0; i<Inputs; i++){
		x->start[i] = TrainingData->start[r*TrainingData->cols + i];
	}
	// copying values into y
	for(int i=0; i<Outputs; i++){
		y->start[i] = TrainingData->start[r*TrainingData->cols + (Inputs + i)];
	}
}

void Dataset::getTestExample(int r, Matrix* x, Matrix* y){
	assert(x->rows == Inputs);
	assert(y->rows == Outputs);
	assert((x->cols == 1) && (y->cols == 1));
	assert((r >= 0) && (r < TrainingData->rows));
	
	//copying values into x
	for(int i=0; i<Inputs; i++){
		x->start[i] = TestData->start[r*TestData->cols + i];
	}
	// copying values into y
	for(int i=0; i<Outputs; i++){
		y->start[i] = TestData->start[r*TestData->cols + (Inputs + i)];
	}
}

Dataset::Dataset(Matrix* data, dataT percent, int input){	
	assert((data->rows * percent) > 0);
	assert(input < data->cols);

	Percentage = percent;
	Inputs = input;
	Outputs = data->cols - input;

	int testrows = data->rows * (1 - Percentage); 
	std::set<int> training;
	std::set<int> test;

	for(int i=1; i<=data->rows; i++){
		training.insert(i);
	}

	while(test.size() != testrows){
		int r = rand() % data->rows;
		if(training.find(r) != training.end()){
			test.insert(r);
			training.erase(r);
		}
	}

	TrainingData = new Matrix(data->rows - testrows, data->cols);
	if(testrows == 0){
		TestData = new Matrix(data->rows, data->cols);
	}
	else{
		TestData = new Matrix(testrows, data->cols);
	}

	int i = 1;
	for(int r : training){
		TrainingData->copyrow(data, r, i);
		if(test.size() == 0){
			TestData->copyrow(data, r, i);
		}
		i++;
	}
	i=1; 
	for(int r : test){
		TestData->copyrow(data, r, i);
		i++;
	}
}

Dataset::~Dataset(){
	if(TrainingData != nullptr){
		delete(TrainingData);
	}
	if(TestData != nullptr){
		delete(TestData);
	}
}
