#include "../include/activations.hpp"

namespace ActivationF{

	dataT sigmoid(dataT x){
		return 1 / (1 + exp(-x));
	}

	dataT sigmoidD(dataT x){
		return sigmoid(x) * (1-sigmoid(x));
	}

	// Matrix Functions
	void NM_sigmoid(NMatrix::Matrix* M){
		assert(M->rows != 0);
		assert(M->cols != 0);
		assert(M->start != nullptr);

		for(i=0; i<M->rows; i++){
			for(j=0; j<M->cols; j++){
				M->start[i*M->cols + j] = sigmoid(M->start[i*M->cols + j]);
			}
		}
	}

	void NM_sigmoidD(NMatrix::Matrix* M){
		assert(M->rows != 0);
		assert(M->cols != 0);
		assert(M->start != nullptr);

		for(i=0; i<M->rows; i++){
			for(j=0; j<M->cols; j++){
				M->start[i*M->cols + j] = sigmoidD(M->start[i*M->cols + j]);
			}
		}
	}
}

