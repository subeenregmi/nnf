#include "loss.hpp"

dataT mse(dataT x, dataT y){
	return pow(y-x, 2);
}

dataT mseD(dataT x, dataT y){
	return -2*(y-x);
}

void applyloss(Matrix* l, Matrix* x, Matrix* y, dataT(*lossf)(dataT, dataT)){
	assert(x->rows == y->rows);
	assert(x->rows == l->rows);
	assert(x->cols == y->cols);
	assert(x->cols == l->cols);
	assert(lossf != nullptr);

	for(int i=0; i<x->rows; i++){
		for(int j=0; j<x->cols; j++){
			(*l)[i][j] = lossf((*x)[i][j], (*y)[i][j]);
		}
	}
}




