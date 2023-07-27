#ifndef MATRIX
#define MATRIX

#include "generic.hpp"

namespace NMatrix{
	struct Matrix{
		int rows = 0;
		int cols = 0;
		dataT* start = nullptr;
		~Matrix();
	};

	// Init functions
	void MEMORY_ALLOC(Matrix* M);
	void MEMORY_DEALLOC(Matrix* M);
	void IDENTITY(Matrix* M);
	void RANDOMIZE(Matrix* M);
	void COPY(Matrix* D, Matrix* M);
	
	// Math functions
	void DOT(Matrix* D, Matrix* A, Matrix* B);
	void ADD(Matrix* D, Matrix* A, Matrix* B);
	void SUBTRACT(Matrix* D, Matrix* A, Matrix* B);
	void SCALE(Matrix* M, dataT scalar);	
	void TRANSPOSE(Matrix* M);
	dataT TOTAL(Matrix* M);

	// Miscellaneous functions
	void PRINT(Matrix* M);
	dataT GET_ITEM(Matrix* M, int rows, int cols);
	void SET_ITEM(Matrix* M, dataT item, int rows, int cols);
}
#endif
