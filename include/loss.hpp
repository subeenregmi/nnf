#ifndef LOSS
#define LOSS

#include "generic.hpp"
#include "matrix.hpp"

namespace LossF{
	dataT squared_error(dataT x, dataT y);
	dataT squared_error_D(dataT x, dataT y);

	void NM_squared_error(NMatrix::Matrix* D, NMatrix::Matrix* x, NMatrix::Matrix* y);
	void NM_squared_error_D(NMatrix::Matrix* D, NMatrix::Matrix* x, NMatrix::Matrix* y);
}

#endif
