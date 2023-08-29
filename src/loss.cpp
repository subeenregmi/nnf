#include "loss.hpp"

dataT mse(dataT x, dataT y){
	return pow(y-x, 2);
}

dataT mseD(dataT x, dataT y){
	return -2*(y-x);
}

dataT cel(dataT x, dataT y){
	return -(y*log(x) + (1-y)*log(1-x));
}

dataT celD(dataT x, dataT y){
	return (-y/x) + ((1-y)/(1-x));
}

void applyloss(Matrix* l, Matrix* x, Matrix* y, dataT(*lossf)(dataT, dataT)){
	assert(x->rows == y->rows);
	assert(x->rows == l->rows);
	assert(x->cols == y->cols);
	assert(x->cols == l->cols);
	assert(lossf != nullptr);

	for(int i=0; i<x->rows; i++){
		for(int j=0; j<x->cols; j++){
			l->start[i*l->cols + j] = lossf(x->start[i*l->cols + j], y->start[i*l->cols + j]);
		}
	}
}




