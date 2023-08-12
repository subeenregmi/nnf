#include "neuralnetwork.hpp"

NN::NN(Matrix* l){
	assert(l->rows == 1);
	
	// check if any layer has zero or less neurons (illegal)
	for(int i=0; i<l->cols; i++){
		assert((*l)[0][i] > 0);
	}

	// Create weights 
	for(int i=0; i<l->cols-1; i++){

		int r = (*l)[0][i+1];
		int c = (*l)[0][i];

		Matrix* w = new Matrix(r, c);	
		w->randomize();
		weights.push_back(w);
	}

	for(int i=1; i<l->cols; i++){
		Matrix* b = new Matrix((*l)[0][i], 1);
		b->randomize();
		biases.push_back(b);
	}
	
	for(int i=0; i<l->cols-1; i++){
		Matrix* z = new Matrix((*l)[0][i], 1);
		Matrix* a = new Matrix((*l)[0][i], 1);
		zterms.push_back(z);
		activations.push_back(z);
	}
}

