#ifndef ACTIVATIONS
#define ACTIVATIONS

#include "generic.hpp"
#include "matrix.hpp"

namespace ActivationF{

	dataT sigmoid(dataT x);
	dataT sigmoidD(dataT x);

	// Matrix Functions
	void NM_sigmoid(NMatrix::Matrix* M);
	void NM_sigmoidD(NMatrix::Matrix* M);
}

#endif // ACTIVATIONS
