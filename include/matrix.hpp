#ifndef MATRIX
#define MATRIX

#include "generic.hpp"
#include "doublesubscript.hpp"

namespace NMatrix{
	struct Matrix{
		int rows;
		int cols;
		dataT* start;
		DoubleSubscript operator[](int r);
		Matrix(int row, int col);
		~Matrix();
	};

	// Init functions
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
	void HPRODUCT(Matrix*D, Matrix*A, Matrix* B);

	// Miscellaneous functions
	void PRINT(Matrix* M, std::string label);
	/*
	dataT GET_ITEM(Matrix* M, int rows, int cols);
	void SET_ITEM(Matrix* M, dataT item, int rows, int cols);
	*/
}
#endif
