#include "../include/loss.hpp"

namespace LossF{
	dataT squared_error(dataT x, dataT y){
		return pow(y-x, 2);
	}

	dataT squared_error_D(dataT x, dataT y){
		return 2*(y-x);
	}
	
	void NM_squared_error(NMatrix::Matrix* D, NMatrix::Matrix* x, NMatrix::Matrix* y){
		assert((D->rows == x->rows) == y->rows);
		assert((D->cols == x->cols) == y->cols);
		assert(D->start != nullptr);
		assert(x->start != nullptr);
		assert(y->start != nullptr);
		
		for(int i=0; i<D->rows; i++){
			for(int j=0; j<D->cols; j++){
				D->start[i*D->cols + j] = squared_error(x->start[i*x->cols + j], y->start[i*y->cols + j]);
			}
		}
	}

	void NM_squared_error_D(NMatrix::Matrix* D, NMatrix::Matrix* x, NMatrix::Matrix* y){
		assert((D->rows == x->rows) == y->rows);
		assert((D->cols == x->cols) == y->cols);
		assert(D->start != nullptr);
		assert(x->start != nullptr);
		assert(y->start != nullptr);
		
		for(int i=0; i<D->rows; i++){
			for(int j=0; j<D->cols; j++){
				D->start[i*D->cols + j] = squared_error_D(x->start[i*x->cols + j], y->start[i*y->cols + j]);
			}
		}
	}
}
