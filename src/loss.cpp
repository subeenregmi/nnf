#include "loss.hpp"

void squaredloss(Matrix* x, Matrix* y){
	assert(x->rows == y->rows);
	assert(x->cols == y->cols);
	Matrix c(x->rows, x->cols);
	c.copy(y);
	c.subtract(x);
	x->copy(&c);
	for(int i=0; i<x->rows; i++){
		for(int j=0; j<x->cols; j++){
			(*x)[i][j] *= (*x)[i][j];
		}
	}
}

void squaredlossD(Matrix* x, Matrix* y){
	assert(x->rows == y->rows);
	assert(x->cols == y->cols);
	Matrix c(x->rows, x->cols);
	c.copy(y);
	c.subtract(x);
	x->copy(&c);
}

