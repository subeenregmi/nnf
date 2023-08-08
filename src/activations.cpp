#include "../include/activations.hpp"

// Sigmoid Function
dataT sigmoid(dataT x){
	return 1 / (1 + exp(-x));
}

dataT sigmoidD(dataT x){
	return sigmoid(x) * (1-sigmoid(x));
}



void sigmoid(Matrix* m){
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			(*m)[i][j] = sigmoid((*m)[i][j]);
		}
	}
}

void sigmoidD(Matrix* m){
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			(*m)[i][j] = sigmoidD((*m)[i][j]);
		}
	}
}

// Tanh Function 
dataT tanh(data x){
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

dataT tanhD(data x){
	return 1 - pow(tanh(x), 2);
}


void tanh(Matrix* m){
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			(*m)[i][j] = sigmoidD((*m)[i][j]);
		}
	}
}

void sigmoidD(Matrix* m){
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			(*m)[i][j] = sigmoidD((*m)[i][j]);
		}
	}
}

dataT relu(dataT x){
	if(x<0){
		return 0;
	}
	return x;
}

dataT reluD(dataT x){
	if(x<0){
		return 0;
	}
	return 1;
}


void relu(Matrix* m){
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			(*m)[i][j] = relu((*m)[i][j]);
		}
	}
}

void reluD(Matrix* m){
	for(int i=0; i<m->rows; i++){
		for(int j=0; j<m->cols; j++){
			(*m)[i][j] = reluD((*m)[i][j]);
		}
	}
}
